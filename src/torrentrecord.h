#ifndef TORRENTRECORD_H
#define TORRENTRECORD_H

#include <QByteArray>
#include <QDebug>
#include <QList>
#include <QString>
#include <QStringList>

struct FileInfo
{
    quint64 size;
    qint64 mtime;
    int priority;
};

struct TorrentRecord
{
    QString info_hash;
    QString save_path; // the parent directory
    QString torrent_path;
    QString name;

    // storage info
    uint block_size;
    uint piece_length;
    quint64 piece_count;
    QByteArray pieces_we_have;
    QList<FileInfo> files;

    // statistics
    quint64 total_downloaded;
    quint64 total_uploaded;
    quint64 active_time;
    quint64 seeding_time;
    quint64 added_time;
    quint64 complete_time;
    quint64 last_active;
    quint64 last_seen_complete;

    // per torrent settings
    int max_connections;
    bool sequential_download;
    bool allow_dht;
    bool allow_lsd;
    double ratio_limit;
    bool super_seeding;

    // torrent state
    int seed_mode;
    bool paused;

    // trackers
    QStringList trackers;

    // labels
    QStringList labels;

    enum CONSTANTS {
        MAX_CONNECTIONS_NO = -1
    };
};

QDebug &operator<<(QDebug &out, const TorrentRecord &rec);

#endif // TORRENTRECORD_H
