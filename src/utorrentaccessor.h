#ifndef UTORRENTACCESSOR_H
#define UTORRENTACCESSOR_H

#include <QBencodeValue>
#include "irecordsaccessor.h"

class uTorrentAccessor : public IRecordsAccessor
{
public:
    uTorrentAccessor();
    ~uTorrentAccessor();

    virtual bool setup(QVariantHash args);
    virtual QList<TorrentRecord> readAll();
    virtual bool writeAll(QList<TorrentRecord> &records);
    virtual bool add(const TorrentRecord &record);
    virtual bool update(const TorrentRecord &record);
    virtual bool remove(const QString &hash);

private:
    QString appdataPath;
    QBencodeDict resumeData;

    bool ready;
};

#endif // UTORRENTACCESSOR_H
