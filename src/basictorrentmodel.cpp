#include <QBencodeValue>
#include "basictorrentmodel.h"

BasicTorrentModel::BasicTorrentModel(IRecordsAccessor *accessor, QObject *parent)
    : QAbstractTableModel(parent), accessor(accessor), dirtyCache(false)
{
    accessor->readAll(recordCache);
}

BasicTorrentModel::~BasicTorrentModel()
{
    delete accessor;
}

Qt::ItemFlags BasicTorrentModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index);
}

QVariant BasicTorrentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return displayData(index);
    } else {
        return QVariant();
    }
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

int BasicTorrentModel::rowCount(const QModelIndex &/*parent*/) const
{
    return recordCache.size();
}

int BasicTorrentModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

bool BasicTorrentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role != Qt::UserRole) {
        return false;
    }

    auto benval = QBencodeValue::fromVariant(value);
    if (benval.isUndefined()) {
        return false;
    }
    return false;
}

bool BasicTorrentModel::insertRows(int /*row*/, int /*count*/,
                                   const QModelIndex &/*parent*/)
{
    // FUTURE: BasicTorrentModel::insertRows
    return false;
}

bool BasicTorrentModel::removeRows(int /*row*/, int /*count*/,
                                   const QModelIndex &/*parent*/)
{
    // FUTURE: BasicTorrentModel::removeRows
    return false;
}

void BasicTorrentModel::flush()
{
    // FUTURE: BasicTorrentModel::flush
}

QVariant BasicTorrentModel::displayData(const QModelIndex &/*index*/) const
{
    // FUTURE: BasicTorrentModel::displayData
    return QVariant();
}

void BasicTorrentModel::ensureCache()
{
    if (dirtyCache) {
        accessor->readAll(recordCache);
        dirtyCache = false;
    }
}
