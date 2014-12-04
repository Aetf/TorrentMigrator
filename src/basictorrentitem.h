#ifndef BASICTORRENTITEM_H
#define BASICTORRENTITEM_H

#include <QVariant>
#include "torrentrecord.h"

class BasicTorrentModel;
class BasicTorrentItem
{
public:
    BasicTorrentItem(BasicTorrentModel *model, const TorrentRecord &record = TorrentRecord());
    ~BasicTorrentItem();

    QVariant data(int column = 0, int role = Qt::DisplayRole) const;
    bool setData(const QVariant &value, int role = Qt::DisplayRole);

    Qt::ItemFlags flags() const;

private:
    BasicTorrentModel *model;
    TorrentRecord record;
    bool isNull;
};

#endif // BASICTORRENTITEM_H
