#ifndef ABSTRACTECORDSACCESSOR_H
#define ABSTRACTECORDSACCESSOR_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include "irecordsaccessor.h"
#include "torrentrecord.h"

class TorrentItem;
class BasicTorrentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BasicTorrentModel(IRecordsAccessor *accessor, QObject *parent = 0);
    virtual ~BasicTorrentModel();

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
    virtual bool removeRows(int row, int count, const QModelIndex &parent);

public slots:
    void flush();

protected:
    TorrentItem *createItem();
    QVariant displayData(const QModelIndex &index) const;
    inline void ensureCache();

signals:

private:
    IRecordsAccessor *accessor;

    QList<TorrentRecord> recordCache;
    bool dirtyCache;
};

#endif // ABSTRACTECORDSACCESSOR_H
