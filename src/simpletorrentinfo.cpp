#include <QBencodeDocument>
#include <QBencodeValue>
#include <QDebug>
#include <QFile>
#include "simpletorrentinfo.h"
#include "utils.h"

SimpleTorrentInfo::SimpleTorrentInfo(const QString &filepath)
    : valid(false)
{
    loadFile(filepath);
}

SimpleTorrentInfo::~SimpleTorrentInfo()
{

}

bool SimpleTorrentInfo::loadFile(const QString &filepath)
{
    QFile f(filepath);
    if (!f.open(QIODevice::ReadOnly)) {
        // haven't changed anything, just return
        return false;
    }

    QBencodeValue torrent = QBencodeDocument::fromBencode(f.readAll()).value();
    if (!parseTorrent(torrent)) {
        // we may be partially changed some field, no longer valid
        valid = false;
        return false;
    }
    valid = true;
    return true;
}

bool SimpleTorrentInfo::parseTorrent(const QBencodeValue &torrent)
{
    if (!torrent.isDict()) { return false; }
    if (!torrent.toDict()["info"].isDict()) { return false; }
    auto infoDict = torrent.toDict()["info"].toDict();

    // filename or dirname
    // prefer a utf-8 entry
    file_or_dir_name = infoDict["name.utf-8"].toString();
    if (file_or_dir_name.isEmpty()) { file_or_dir_name = infoDict["name"].toString(); }

    // extract piece length
    piece_length = Utils::dictFindInt(infoDict, "piece length", 0);
    if (piece_length == 0) { return false; }

    // extract files info and calculate total length
    if (!extractFilesInfo(infoDict)) { return false; }

    // calculate piece count
    // this should be round up, that's why the "+ piece_length -1" part
    piece_count = ((total_length + piece_length - 1) / piece_length);

    return true;
}

bool SimpleTorrentInfo::extractFilesInfo(const QBencodeDict &infoDict)
{
    if (!infoDict.contains("files")) {
        // no file list, a single file torrent assumed.
        // must have a length then.
        total_length = Utils::dictFindLongLong(infoDict, "length", 0);
        if (total_length == 0) { return false; }
        file_sizes.append(total_length);

        file_mtimes.append(Utils::dictFindInt(infoDict, "mtime", 0));
    } else {
        total_length = 0;
        if (!infoDict.value("files").isList()) { return false; }
        auto list = infoDict.value("files").toList();

        for (auto entry : list) {
            if (!entry.isDict()) { return false; }
            auto fd = entry.toDict();

            auto l = Utils::dictFindLongLong(fd, "length", -1);
            if (l < 0) { return false; }
            auto mt = Utils::dictFindLongLong(fd, "mtime", 0);

            total_length += Utils::dictFindLongLong(fd, "length", 0);
            file_sizes.append(l);
            file_mtimes.append(mt);
        }
    }
    return true;
}
