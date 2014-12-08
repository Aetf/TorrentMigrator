#ifndef ABSTRACTECORDSACCESSOR_H
#define ABSTRACTECORDSACCESSOR_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include "irecordsaccessor.h"
#include "torrentrecord.h"

class BasicTorrentItem;

class BasicTorrentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles {
        RecordDataRole = Qt::UserRole + 1,
    };

    enum Columns {
        Col_No = 0,
        Col_Name,
        Col_TorrentPath,
        Col_SavePath,
        Col_State,
        ColCount,
    };

    explicit BasicTorrentModel(IRecordsAccessor *accessor, QObject *parent = 0);
    virtual ~BasicTorrentModel();

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool insertRecord(int position, const TorrentRecord &record);
public slots:
    bool pullData();
    void clear();

protected:
    bool insertRowsWithoutAddToBackend(int position, const QList<BasicTorrentItem *> rows);
    bool inRange(const QModelIndex &index) const;
    QVariant dataForColNo(int row, int roel) const;

signals:

private:
    IRecordsAccessor *accessor;

    QList<BasicTorrentItem *> items;

    friend class BasicTorrentItem;
};

#endif // ABSTRACTECORDSACCESSOR_H
