#ifndef ABSTRACTECORDSACCESSOR_H
#define ABSTRACTECORDSACCESSOR_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include "irecordsaccessor.h"

class TorrentItem;
class BasicTorrentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BasicTorrentModel(QObject *parent = 0);
    virtual ~BasicTorrentModel();

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
    virtual bool removeRows(int row, int count, const QModelIndex &parent);

protected:
    TorrentItem *createItem();

signals:

public slots:
};

#endif // ABSTRACTECORDSACCESSOR_H
