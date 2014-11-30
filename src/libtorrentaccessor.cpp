#include <QBencodeDocument>
#include <QBencodeValue>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QSettings>
#include "libtorrentaccessor.h"
#include "simpletorrentinfo.h"

LibtorrentAccessor::LibtorrentAccessor()
    : ready(false)
{

}

LibtorrentAccessor::~LibtorrentAccessor()
{

}

bool LibtorrentAccessor::setup(QVariantHash args)
{
    configDir = args["configDir"].toString();
    backupDir = args["backupDir"].toString();

    ready = true;
    return true;
}

bool LibtorrentAccessor::readAll(QList<TorrentRecord> &list)
{
    if (!ready) { return false; }

    auto torrents = recordHashs();

    list.reserve(torrents.size());
    for (auto hash : torrents) {
        if (!hasResumeData(hash)) {
            qDebug() << "skip record without fastresume data:" << hash;
            continue;
        }
        auto pair = locateTorrentFile(hash);
        if (!pair.first.isValid()) {
            qDebug() << "skip record without torrent data:" << hash;
            continue;
        }
        auto ti = pair.first;

        TorrentRecord record;
        record.info_hash = hash;
        record.save_path = getSavePath(hash);
        record.name = ti.name();

        // storage info
        if (!fillStorageInfo(record, hash, ti)) { continue; }
        fillFileInfos(record, hash);

        // statistics
        record.total_downloaded = getResumeValue(hash, "total_downloaded").toULongLong();
        record.total_uploaded = getResumeValue(hash, "total_uploaded").toULongLong();
        record.active_time = getResumeValue(hash, "active_time").toULongLong();
        record.seeding_time = getResumeValue(hash, "seeding_time").toULongLong();
        record.added_time = getAddedDate(hash).toTime_t();
        //        record.added_time = getResumeValue(hash, "added_time").toULongLong();
        record.complete_time = getResumeValue(hash, "complete_time").toULongLong();
        fillLastActive(record, hash);
        record.last_seen_complete = getResumeValue(hash, "last_seen_complete").toULongLong();

        // per torrent settings
        fillMaxConnections(record, hash);
        record.sequential_download = getResumeValue(hash, "sequential_download").toInt() != 0;
        record.allow_dht = getResumeValue(hash, "announce_to_dht").toInt() != 0;
        record.allow_lsd = getResumeValue(hash, "announce_to_lsd").toInt() != 0;
        fillRatioLimit(record, hash);
        record.super_seeding = getResumeValue(hash, "super_seeding").toInt() != 0;

        // torrent state
        record.seed_mode = getResumeValue(hash, "seed_mode").toInt();
        record.paused = 1;

        // trackers
        fillTrackers(record, hash);

        // labels
        fillLabels(record, hash);

        list.append(record);
    }

    return true;
}

bool LibtorrentAccessor::writeAll(QList<TorrentRecord> &records)
{
    if (!ready) { return false; }

    for (auto r : records) {
        if (!add(r)) { return false; }
    }
    return true;
}

bool LibtorrentAccessor::add(const TorrentRecord &/*record*/)
{
    if (!ready) { return false; }

    // TODO: write support for libtorrent
    return false;
}

bool LibtorrentAccessor::update(const TorrentRecord &/*record*/)
{
    if (!ready) { return false; }

    // TODO: write support for libtorrent
    return false;
}

bool LibtorrentAccessor::remove(const QString &/*hash*/)
{
    if (!ready) { return false; }

    // TODO: write support for libtorrent
    return false;
}

QStringList LibtorrentAccessor::recordHashs()
{
    QSettings settings(configDir + "/qBittorrent-resume.conf", QSettings::IniFormat);
    return settings.value("torrents").toHash().keys();
}

void LibtorrentAccessor::deleteConfRecord(const QString &hash)
{
    QSettings settings(configDir + "/qBittorrent-resume.conf", QSettings::IniFormat);
    auto torrents = settings.value("torrents").toHash();
    if (torrents.contains(hash)) {
        torrents.remove(hash);
        settings.setValue("torrents", torrents);
    }
}

bool LibtorrentAccessor::fillStorageInfo(TorrentRecord &record, const QString &hash,
                                         const SimpleTorrentInfo &ti)
{
    if (!ti.isValid()) { return false; }

    record.piece_length = ti.pieceLength();
    record.block_size = record.piece_length / getBlocksPerPiece(hash);
    record.piece_count = ti.pieceCount();
    record.pieces_we_have = getResumeValue(hash, "pieces").toByteArray();

    return true;
}

void LibtorrentAccessor::fillFileInfos(TorrentRecord &record, const QString &hash)
{
    auto files = getResumeValue(hash, "file sizes").toList();
    auto filePrio = getResumeValue(hash, "file_priority").toList();
    record.files.clear();
    record.files.reserve(files.size());

    for (int i = 0; i != files.size(); i++) {
        auto fl = files[i].toList();

        FileInfo fi;
        fi.size = fl[0].toULongLong();
        fi.mtime = fl[1].toULongLong();
        fi.priority = filePrio[i].toInt();

        record.files.append(fi);
    }
}

void LibtorrentAccessor::fillLastActive(TorrentRecord &record, const QString &hash)
{
    auto last_uploaded = getResumeValue(hash, "last_uploaded").toULongLong();
    auto last_downloaded = getResumeValue(hash, "last_downloaded").toULongLong();

    record.last_active = qMax(last_downloaded, last_uploaded);
}

void LibtorrentAccessor::fillMaxConnections(TorrentRecord &record, const QString &hash)
{
    auto temp = getResumeValue(hash, "max_connections", MAX_CONNECTION_NO).toInt();

    if (temp == MAX_CONNECTION_NO) {
        temp = TorrentRecord::MAX_CONNECTIONS_NO;
    }

    record.max_connections = temp;
}

void LibtorrentAccessor::fillRatioLimit(TorrentRecord &record, const QString &hash)
{
    auto temp = getRatioLimit(hash);

    if (temp == USE_GLOBAL_RATIO) {
        // TODO: handle global ratio
    }
    record.ratio_limit = temp;
}

void LibtorrentAccessor::fillTrackers(TorrentRecord &record, const QString &hash)
{
    auto outer = getResumeValue(hash, "trackers").toList();
    record.trackers.clear();
    record.trackers.reserve(outer.size());

    for (auto inner : outer) {
        record.trackers.append(inner.toList()[0].toString());
    }
}

void LibtorrentAccessor::fillLabels(TorrentRecord &record, const QString &hash)
{
    // TODO: multi label support
    record.labels.clear();
    record.labels.append(getResumeValue(hash, "qBt-label").toString());
}

void LibtorrentAccessor::setConfValue(const QString &hash, const QString &key,
                                      const QVariant &value)
{
    QSettings settings(configDir + "/qBittorrent-resume.conf", QSettings::IniFormat);
    auto torrents = settings.value("torrents").toHash();
    auto record = torrents.value(hash).toHash();
    record[key] = value;
    settings.setValue("torrents", torrents);
}

QVariant LibtorrentAccessor::getConfValue(const QString &hash, const QString &key,
                                          const QVariant &defaultVal) const
{
    QSettings settings(configDir + "/qBittorrent-resume.conf", QSettings::IniFormat);
    const auto record = settings.value("torrents").toHash().value(hash).toHash();
    return defaultVal.isValid() ? record.value(key, defaultVal) : record.value(key);
}

bool LibtorrentAccessor::hasResumeData(const QString &hash) const
{
    QFile f(backupDir + "/" + hash + ".fastresume");
    return f.exists();
}

QVariant LibtorrentAccessor::getResumeValue(const QString &hash, const QString &key,
                                            const QVariant &defaultVal) const
{
    QFile f(backupDir + "/" + hash + ".fastresume");
    if (!f.open(QIODevice::ReadOnly)) { return defaultVal; }

    QBencodeValue resume = QBencodeDocument::fromBencode(f.readAll()).value();
    if (!resume.isDict()) { return defaultVal; }

    auto dict = resume.toDict();
    if (!dict.contains(key)) { return defaultVal; }

    return dict.value(key).toVariant();
}

std::pair<SimpleTorrentInfo, QString> LibtorrentAccessor::locateTorrentFile(
    const QString &hash)
{
    QString fullpath(backupDir + "/" + hash + ".torrent");
    SimpleTorrentInfo ti(fullpath);
    return std::make_pair(ti, QDir::cleanPath(fullpath));
}

void LibtorrentAccessor::setRatioLimit(const QString &hash, double ratio)
{
    setConfValue(hash, "max_ratio", ratio);
}

double LibtorrentAccessor::getRatioLimit(const QString &hash)
{
    return getConfValue(hash, "max_ratio", USE_GLOBAL_RATIO).toDouble();
}

void LibtorrentAccessor::setAddedDate(const QString &hash, const QDateTime &time)
{
    setConfValue(hash, "add_date", time);
}

QDateTime LibtorrentAccessor::getAddedDate(const QString &hash)
{
    return getConfValue(hash, "add_date").toDateTime();
}

void LibtorrentAccessor::setSeedDate(const QString &hash, const QDateTime &time)
{
    setConfValue(hash, "seed_date", time);
}

QDateTime LibtorrentAccessor::getSeedDate(const QString &hash)
{
    return getConfValue(hash, "seed_date").toDateTime();
}

void LibtorrentAccessor::setSavePath(const QString &hash, const QString &save_path)
{
    setConfValue(hash, "save_path", save_path);
}

void LibtorrentAccessor::setLabel(const QString &hash, const QString &label)
{
    setConfValue(hash, "label", label);
}

void LibtorrentAccessor::setName(const QString &hash, const QString &name)
{
    setConfValue(hash, "name", name);
}

void LibtorrentAccessor::setPriority(const QString &hash, const int &queue_pos)
{
    setConfValue(hash, "priority", queue_pos);
}

void LibtorrentAccessor::setSeedStatus(const QString &hash, const bool seedStatus)
{
    setConfValue(hash, "seed", seedStatus);
}

QString LibtorrentAccessor::getSavePath(const QString &hash)
{
    return getConfValue(hash, "save_path").toString();
}

QString LibtorrentAccessor::getLabel(const QString &hash)
{
    return getConfValue(hash, "label").toString();
}

QString LibtorrentAccessor::getName(const QString &hash)
{
    return getConfValue(hash, "name").toString();
}

int LibtorrentAccessor::getPriority(const QString &hash)
{
    return getConfValue(hash, "priority").toInt();
}

bool LibtorrentAccessor::isSeed(const QString &hash)
{
    return getConfValue(hash, "seed", false).toBool();
}

int LibtorrentAccessor::getBlocksPerPiece(const QString &hash)
{
    return getResumeValue(hash, "blocks per piece").toInt();
}
