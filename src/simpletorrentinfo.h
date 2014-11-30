#ifndef TORRENTINFO_H
#define TORRENTINFO_H

#include <QList>
#include <QString>

class QBencodeDict;
class QBencodeValue;

class SimpleTorrentInfo
{
public:
    SimpleTorrentInfo() : valid(false) {}
    SimpleTorrentInfo(const QString &filepath);
    ~SimpleTorrentInfo();

    bool loadFile(const QString &filepath);

    bool isValid() const { return valid; }

    QString name() const { return file_or_dir_name; }
    uint pieceLength() const { return piece_length; }
    uint pieceCount() const { return piece_count; }
    quint64 totalLength() const { return total_length; }
    const QList<quint64> fileSizes() const { return file_sizes; }
    const QList<qint64> fileMTimes() const { return file_mtimes; }

protected:
    bool parseTorrent(const QBencodeValue &torrent);
    bool extractFilesInfo(const QBencodeDict &infoDict);

private:
    bool valid;

    uint piece_length;
    uint piece_count;
    quint64 total_length;
    QList<quint64> file_sizes;
    QList<qint64> file_mtimes;
    QString file_or_dir_name;
};

#endif // TORRENTINFO_H
