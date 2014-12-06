#include <QBencodeValue>
#include "basictorrentmodel.h"
#include "basictorrentitem.h"

BasicTorrentModel::BasicTorrentModel(IRecordsAccessor *accessor, QObject *parent)
    : QAbstractTableModel(parent), accessor(accessor)
{
    pullData();
}

BasicTorrentModel::~BasicTorrentModel()
{
    clear();
    delete accessor;
}

Qt::ItemFlags BasicTorrentModel::flags(const QModelIndex &index) const
{
    if (!inRange(index)) {
        return QAbstractTableModel::flags(index);
    } else {
        return items[index.row()]->flags();
    }
}

QVariant BasicTorrentModel::data(const QModelIndex &index, int role) const
{
    if (!inRange(index)) {
        return QVariant();
    }

    if (index.column() == Col_No) {
        return index.row();
    }

    return items[index.row()]->data(index.column(), role);
}

QVariant BasicTorrentModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
    if (orientation != Qt::Horizontal) { return QVariant(); }

    if (role != Qt::DisplayRole) { return QVariant(); }

    switch (section) {
    case 0:
        return tr("No.");
    case 1:
        return tr("Name");
    case 2:
        return tr("Torrent");
    case 3:
        return tr("Save Path");
    case 4:
        return tr("State");
    default:
        return QVariant();
    }
}

int BasicTorrentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) { return 0; }
    return items.size();
}

int BasicTorrentModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) { return 0; }
    return ColCount;
}

bool BasicTorrentModel::insertRowsWithoutAddToBackend(int position, const QList<BasicTorrentItem *> rows)
{
    QModelIndex idx;
    beginInsertRows(idx, position, position + rows.size() - 1);
    for (auto row : rows) {
        items.insert(position, row);
    }
    endInsertRows();
    return true;
}

bool BasicTorrentModel::insertRecord(int position, const TorrentRecord &record)
{
    if (!accessor->add(record)) {
        qDebug() << "Underlying backend insertion failed.";
        return false;
    }
    QList<BasicTorrentItem *> rowsToInsert;
    rowsToInsert << new BasicTorrentItem(this, record);
    return insertRowsWithoutAddToBackend(position, rowsToInsert);
}

bool BasicTorrentModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()) {
        return false;
    }

    if (row + count > items.size()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    while (count--) {
        items.removeAt(row);
    }
    endRemoveRows();
    return false;
}

bool BasicTorrentModel::inRange(const QModelIndex &index) const
{
    return index.isValid() && index.row() >= 0 && index.row() < items.size()
           && index.column() >= 0 && index.column() < 5;
}

void BasicTorrentModel::clear()
{
    qDeleteAll(items);
    items.clear();
}

bool BasicTorrentModel::pullData()
{
    QList<TorrentRecord> records;
    if (!accessor->readAll(records)) { return false; }

    clear();
    QList<BasicTorrentItem *> rowsToInsert;
    for (auto record : records) {
        rowsToInsert << new BasicTorrentItem(this, record);
    }
    return insertRowsWithoutAddToBackend(0, rowsToInsert);
}
