#include <QBencodeDocument>
#include <QBencodeValue>
#include <QByteArray>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <cassert>
#include "simpletorrentinfo.h"
#include "utorrentaccessor.h"
#include "utils.h"

uTorrentAccessor::uTorrentAccessor()
    : ready(false)
{ }

uTorrentAccessor::~uTorrentAccessor()
{ }

IRecordsAccessor* uTorrentAccessor::allocate() const
{
    return new uTorrentAccessor();
}

QString uTorrentAccessor::name() const
{
    return QStringLiteral("uTorrent");
}

/*!
 * \brief setup
 * \param args
 *     "appdata" => path to appdata dir
 *     "extratorrent" => path to extratorrent dir
 * \return
 */
bool uTorrentAccessor::setup(QVariantMap args)
{
    appdataPath = args["appdata"].toString();
    extraTorrentPath = args["extratorrent"].toString();

    ready = loadResumeData();
    return ready;
}

bool uTorrentAccessor::loadResumeData()
{
    QFile resumeFile(appdataPath + "/resume.dat");
    if (!resumeFile.open(QIODevice::ReadOnly)) {
        qDebug() << "file open failed on" << resumeFile.fileName();
        return false;
    }

    auto doc = QBencodeDocument::fromBencode(resumeFile.readAll());
    if (doc.isNull()) {
        qDebug() << "invalid bencode format in file" << resumeFile.fileName();
        return false;
    }

    // quick sanity check, valid resume data should have a dict as root
    if (doc.value().type() != QBencodeValue::Dict) {
        qDebug() << "valid format but wrong type in file" << resumeFile.fileName();
        return false;
    }

    resumeData = doc.value().toDict();

    return true;
}

bool uTorrentAccessor::writeResumeData()
{
    Utils::ensurePath(appdataPath);
    QFile resumeFile(appdataPath + "/resume.dat");
    if (!resumeFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "file open failed on" << resumeFile.fileName();
        return false;
    }

    // remove .fileguard so uTorrent will accept the file
    if (resumeData.contains(".fileguard")) {
        resumeData.remove(QString::fromUtf8(".fileguard"));
    }

    QBencodeDocument doc;
    doc.setValue(resumeData);
    if (resumeFile.write(doc.toBencode()) == -1) {
        qDebug() << "error when writing file" << resumeFile.fileName();
        return false;
    }
    return true;
}

bool uTorrentAccessor::add(TorrentRecord &/*record*/)
{
    if (!ready) { return false; }

    // FUTURE: uTorrent: write support
    return false;
}

bool uTorrentAccessor::remove(const QString &hash)
{
    if (!ready) { return false; }

    for (auto key : resumeData.keys()) {
        if (resumeData[key].type() != QBencodeValue::Dict) { continue; }
        auto uTorrentRecord = resumeData[key].toDict();

        auto hashbytes = QByteArray::fromHex(hash.toLatin1());
        if (uTorrentRecord["info"].toByteArray() == hashbytes) {
            auto pair = loadTorrentFile(key);
            if (pair.first.isValid()) {
                if (!QFile(pair.second).remove()) {
                    qDebug() << "can't remove" << pair.second;
                    return false;
                }
            }
            resumeData.remove(key);
            if (!writeResumeData()) { return false; }
            return true;
        }
    }
    return false;
}

bool uTorrentAccessor::update(const TorrentRecord &/*record*/)
{
    if (!ready) { return false; }
    // FUTURE: uTorrent: write support
    /*
        for (auto key : resumeData.keys()) {
            if (resumeData[key].type() != QBencodeValue::Dict) continue;
            auto dict = resumeData[key].toDict();

            auto hashbytes = QByteArray::fromHex(record.info_hash.toLatin1());
            if (dict["info"].toByteArray() == hashbytes) {

                return true;
            }
        }
    */
    return false;
}

bool uTorrentAccessor::readAll(QList<TorrentRecord> &list)
{
    if (!ready) { return false; }

    for (auto key : resumeData.keys()) {
        if (resumeData[key].type() != QBencodeValue::Dict) { continue; }
        auto uTorrentRecord = resumeData[key].toDict();

        TorrentRecord record;
        record.info_hash = uTorrentRecord["info"].toByteArray().toHex();
        fillSavePath(record, uTorrentRecord);
        record.name = uTorrentRecord["caption"].toString();

        // storage info
        if (!fillStorageInfo(record, uTorrentRecord, key)) { continue; }

        // statistics
        record.total_downloaded = Utils::dictFindLongLong(uTorrentRecord, "downloaded", 0);
        record.total_uploaded = Utils::dictFindLongLong(uTorrentRecord, "uploaded", 0);
        record.active_time = Utils::dictFindLongLong(uTorrentRecord, "runtime", 0);
        record.seeding_time = Utils::dictFindLongLong(uTorrentRecord, "seedtime", 0);
        record.added_time = Utils::dictFindLongLong(uTorrentRecord, "added_on", 0);
        record.complete_time = Utils::dictFindLongLong(uTorrentRecord, "completed_on", 0);
        record.last_active = Utils::dictFindLongLong(uTorrentRecord, "last_active", 0);
        record.last_seen_complete = Utils::dictFindLongLong(uTorrentRecord, "last seen complete", 0);

        // per torrent settings
        record.max_connections = Utils::dictFindInt(uTorrentRecord, "max_connections", 0);
        if (record.max_connections == MAX_CONNECTIONS_NO) {
            record.max_connections = TorrentRecord::MAX_CONNECTIONS_NO;
        }
        // FUTURE: uTorrent: sequential download
        record.sequential_download = false;
        // FUTURE: uTorrent: dht meaning
        record.allow_dht = Utils::dictFindInt(uTorrentRecord, "dht", 2) != 2;
        record.allow_lsd = Utils::dictFindInt(uTorrentRecord, "lsd", 0) != 0;
        record.ratio_limit = Utils::dictFindInt(uTorrentRecord, "wanted_ratio", 0);
        record.super_seeding = Utils::dictFindInt(uTorrentRecord, "superseed", 0) != 0;

        // torrent state
        // FUTURE: uTorrent: download mode support
        record.seed_mode = 1;
        record.paused = true;

        // trackers
        for (auto trackerentry : uTorrentRecord["trackers"].toList()) {
            record.trackers.append(trackerentry.toString());
        }

        // labels
        // FUTURE: uTorrent: multi label support
        record.labels.append(uTorrentRecord["label"].toString());
        for (auto labelentry : uTorrentRecord["labels"].toList()) {
            record.labels.append(labelentry.toString());
        }
        record.labels.removeDuplicates();

        list.append(record);
    }

    return true;
}

bool uTorrentAccessor::writeAll(QList<TorrentRecord> &records)
{
    if (!ready) { return false; }

    for (auto r : records) {
        if (!add(r)) { return false; }
    }
    return true;
}

bool uTorrentAccessor::fillStorageInfo(TorrentRecord &record,
                                       const QBencodeDict &uTorrentRecord, const QString &key)
{
    auto pair = loadTorrentFile(key);
    if (!pair.first.isValid()) {
        qDebug() << "can't find a torrent file for the record" << key;
        return false;
    }
    auto ti = pair.first;

    record.torrent_path = pair.second;

    record.piece_length = ti.pieceLength();
    record.block_size = Utils::dictFindInt(uTorrentRecord, "blocksize", 0);
    record.piece_count = ti.pieceCount();

    // convert pieces bitmap
    auto bitmap = uTorrentRecord["have"].toByteArray();
    QByteArray bitArray;
    Utils::extendBitmap(bitArray, bitmap);
    // trim paddings
    // TODO: uTorrent: determin the order of bits in the last byte in bitmap
    // example:
    // Byte in map:    0    7
    // Bits:        0000 0111
    //                    ^^^
    // Order1:            321
    // Order2:            123 (now use this one for simplicity)
    int quotient = record.piece_count / 8;
    int reminder = record.piece_count % 8;
    record.pieces_we_have.clear();
    record.pieces_we_have.append(bitArray.left(quotient * 8));
    record.pieces_we_have.append(bitArray.right(reminder));
    assert((quint64)record.pieces_we_have.size() == record.piece_count);

    // files
    record.files.clear();
    record.files.reserve(ti.fileSizes().size());
    auto priorityArray = uTorrentRecord["prio"].toByteArray();
    if (priorityArray.size() != ti.fileSizes().size()) {
        qDebug() << "file count mismatch with prio count for torrent"
                 << key << "with priorityArray" << priorityArray.toHex();
        return false;
    }

    for (int i = 0; i != ti.fileSizes().size(); i++) {
        FileInfo fi;
        fi.size = ti.fileSizes()[i];
        fi.mtime = ti.fileMTimes()[i];
        if (fi.mtime == 0) {
            fi.mtime = uTorrentRecord["modtimes"].toList()[i].toInteger();
        }
        fi.priority = priorityArray.at(i);

        record.files.append(fi);
    }

    return true;
}

void uTorrentAccessor::fillSavePath(TorrentRecord &record, const QBencodeDict &uTorrentRecord)
{
    QString path = Utils::normalizeSeperator(uTorrentRecord["path"].toString());
    path = QDir::cleanPath(path);
    Q_ASSERT(!path.isEmpty());

    // should only save parent directory
    path = path.left(path.lastIndexOf('/') + 1);
    Q_ASSERT(!path.isEmpty());

    record.save_path = path;
}

std::pair<SimpleTorrentInfo, QString> uTorrentAccessor::loadTorrentFile(
    const QString &key)
{
    // Qt can't handle back slash when compiled in linux
    // so change all to slash
    auto filename = QFileInfo(Utils::normalizeSeperator(key)).fileName();
    QDir dir;
    QString fullpath;
    SimpleTorrentInfo ti;

    // try appdata dir first
    dir.setPath(appdataPath);
    fullpath = dir.filePath(filename);
    qDebug() << "uTorrentAccessor: try" << fullpath;
    if (ti.loadFile(fullpath)) { return std::make_pair(ti, fullpath); }

    // then try extra torrent dir if we have one
    if (!extraTorrentPath.isEmpty()) {
        dir.setPath(extraTorrentPath);
        fullpath = dir.filePath(filename);
        qDebug() << "uTorrentAccessor: try" << fullpath;
        if (ti.loadFile(fullpath)) { return std::make_pair(ti, fullpath); }
    }

    return std::make_pair(ti, QString());
}
