#ifndef BASICTORRENTITEM_H
#define BASICTORRENTITEM_H

#include <QVariant>
#include "torrentrecord.h"

class BasicTorrentModel;
class BasicTorrentItem
{
public:
    BasicTorrentItem(BasicTorrentModel *m_model, const TorrentRecord &m_record = TorrentRecord());
    ~BasicTorrentItem();

    QVariant data(int column = 0, int role = Qt::DisplayRole) const;
    bool setData(const QVariant &value, int role = Qt::DisplayRole);

    Qt::ItemFlags flags() const;
    const TorrentRecord &record() const { return m_record; }

private:
    BasicTorrentModel *m_model;
    TorrentRecord m_record;
    bool isNull;
};

#endif // BASICTORRENTITEM_H
