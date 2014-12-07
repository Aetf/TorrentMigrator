#ifndef IRECORDSTRANSFORMER_H
#define IRECORDSTRANSFORMER_H

#include <QVariantHash>
#include "torrentrecord.h"

class IRecordsTransformer
{
public:
    virtual ~IRecordsTransformer() { }

    virtual bool setup(QString args) = 0;
    virtual bool setup(QVariantHash args) = 0;
    virtual TorrentRecord transform(const TorrentRecord &input) const = 0;
    virtual TorrentRecord transformBack(const TorrentRecord &input) const = 0;
};

#endif // IRECORDSTRANSFORMER_H

