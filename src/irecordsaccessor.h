#ifndef ABSTRACTBACKEND_H
#define ABSTRACTBACKEND_H

#include <QList>
#include <QVariant>
#include <QHash>
#include "torrentrecord.h"

class IRecordsAccessor
{
public:
    virtual ~IRecordsAccessor() = 0;

    virtual bool setup(QVariantHash args) = 0;
    virtual QList<TorrentRecord> readAll() = 0;
    virtual bool writeAll(QList<TorrentRecord> &records) = 0;
    virtual bool add(const TorrentRecord &record) = 0;
    virtual bool update(const TorrentRecord &record) = 0;
    virtual bool remove(const QString &hash) = 0;
};

#endif // ABSTRACTBACKEND_H
