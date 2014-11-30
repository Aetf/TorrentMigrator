#include "torrentrecord.h"

QDebug &operator<<(QDebug &out, const TorrentRecord &rec)
{
    out << "TorrentRecord{" << rec.save_path << rec.info_hash;
    return out;
}
