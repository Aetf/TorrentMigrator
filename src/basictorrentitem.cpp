#include "basictorrentitem.h"
#include "basictorrentmodel.h"

BasicTorrentItem::BasicTorrentItem(BasicTorrentModel *model, const TorrentRecord &record)
    : model(model), record(record), isNull(true)
{
}

BasicTorrentItem::~BasicTorrentItem()
{

}

QVariant BasicTorrentItem::data(int column, int role) const
{
    if (role == Qt::UserRole + 1) {
        return QVariant::fromValue(record);
    }

    if (role == Qt::DisplayRole) {
        switch (column) {
        case BasicTorrentModel::Col_Name:
            return record.name;
        case BasicTorrentModel::Col_TorrentPath:
            return record.torrent_path;
        case BasicTorrentModel::Col_SavePath:
            return record.save_path;
        case BasicTorrentModel::Col_TorrentState:
            return record.paused ? QObject::tr("Paused") : QObject::tr("Normal");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

bool BasicTorrentItem::setData(const QVariant &value, int role)
{
    if (role == Qt::UserRole + 1) {
        auto rec = value.value<TorrentRecord>();
        bool hashChanged = (record.info_hash == rec.info_hash);
        bool ok = true;

        if (isNull || hashChanged) {
            ok = model->accessor->add(record);
        } else {
            ok = model->accessor->update(record);
        }
        if (!ok) { return false; }

        record = rec;
        isNull = false;
        return true;
    }
    return false;
}

Qt::ItemFlags BasicTorrentItem::flags() const
{
    return Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


