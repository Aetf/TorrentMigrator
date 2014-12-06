#include "basictorrentitem.h"
#include "basictorrentmodel.h"

BasicTorrentItem::BasicTorrentItem(BasicTorrentModel *model, const TorrentRecord &record)
    : m_model(model), m_record(record), isNull(true)
{
}

BasicTorrentItem::~BasicTorrentItem()
{

}

QVariant BasicTorrentItem::data(int column, int role) const
{
    if (role == Qt::UserRole + 1) {
        return QVariant::fromValue(m_record);
    }

    if (role == Qt::DisplayRole) {
        switch (column) {
        case BasicTorrentModel::Col_Name:
            return m_record.name;
        case BasicTorrentModel::Col_TorrentPath:
            return m_record.torrent_path;
        case BasicTorrentModel::Col_SavePath:
            return m_record.save_path;
        case BasicTorrentModel::Col_State:
            return m_record.paused ? QObject::tr("Paused") : QObject::tr("Normal");
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
        bool hashChanged = (m_record.info_hash == rec.info_hash);
        bool ok = true;

        if (isNull || hashChanged) {
            ok = m_model->accessor->add(m_record);
        } else {
            ok = m_model->accessor->update(m_record);
        }
        if (!ok) { return false; }

        m_record = rec;
        isNull = false;
        return true;
    }
    return false;
}

Qt::ItemFlags BasicTorrentItem::flags() const
{
    return Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


