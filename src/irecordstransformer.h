#ifndef IRECORDSTRANSFORMER_H
#define IRECORDSTRANSFORMER_H

#include <QVariantMap>
#include "torrentrecord.h"

class IRecordsTransformer
{
public:
    virtual ~IRecordsTransformer() { }

    virtual IRecordsTransformer* allocate() const = 0;
    virtual QString name() const = 0;

    virtual bool setup(QString args) = 0;
    virtual bool setup(QVariantMap args) = 0;
    virtual TorrentRecord transform(const TorrentRecord &input) const = 0;
    virtual TorrentRecord transformBack(const TorrentRecord &input) const = 0;
};

#endif // IRECORDSTRANSFORMER_H

