#ifndef ABSTRACTBACKEND_H
#define ABSTRACTBACKEND_H

#include <QList>
#include <QVariant>
#include <QMap>
#include "torrentrecord.h"

class IRecordsAccessor
{
public:
    virtual ~IRecordsAccessor() { }

    virtual IRecordsAccessor* allocate() const = 0;
    virtual QString name() const = 0;

    virtual bool setup(QVariantMap args) = 0;
    virtual bool readAll(QList<TorrentRecord> &list) = 0;
    virtual bool writeAll(QList<TorrentRecord> &records) = 0;
    virtual bool add(TorrentRecord &record) = 0;
    virtual bool update(const TorrentRecord &record) = 0;
    virtual bool remove(const QString &hash) = 0;
};

#endif // ABSTRACTBACKEND_H
