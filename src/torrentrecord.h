#ifndef TORRENTRECORD_H
#define TORRENTRECORD_H

#include <QByteArray>
#include <QList>
#include <QString>
#include <QStringList>

struct FileInfo
{
    quint64 size;
    quint64 mtime;
    int priority;
};

struct TorrentRecord
{
    QString info_hash;
    QString save_path; // the parent directory

    // storage info
    uint block_size;
    uint piece_length;
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
    int max_uploads;
    int upload_rate_limit;
    int download_rate_limit;
    bool sequential_download;
    bool allow_dht;
    bool allow_lsd;
    double radoi_limit;
    bool super_seeding;

    // torrent state
    int seed_mode;
    bool paused;

    // trackers
    QStringList trackers;

    // labels
    QStringList labels;
};

#endif // TORRENTRECORD_H
