#include "recordsmodel.h"
#include "recordsaccessorobject.h"

RecordsModel::RecordsModel(QObject *parent) : QIdentityProxyModel(parent)
{
    connect(this, &RecordsModel::sourceModelChanged,
            this, &RecordsModel::onSourceModelChanged);
}

RecordsModel::~RecordsModel()
{
}

void RecordsModel::onSourceModelChanged()
{
    auto model = qobject_cast<BasicTorrentModel*>(sourceModel());
    if (model) {
        connect(model, &BasicTorrentModel::taskRunningChanged,
                this, &RecordsModel::busyChanged);
        emit busyChanged();
    }
}

RecordsAccessorObject *RecordsModel::accessor() const
{
    return m_accessor;
}

void RecordsModel::setAccessor(RecordsAccessorObject *accessor)
{
    if (accessor != m_accessor) {
        m_accessor = accessor;
        if (m_accessor && m_accessor->parent() == nullptr) {
            m_accessor->setParent(this);
        }

        auto oldModel = sourceModel();
        if (m_accessor && m_accessor->get()) {
            setSourceModel(new BasicTorrentModel(m_accessor->take(), this));
        } else {
            setSourceModel(nullptr);
        }
        delete oldModel;

        emit accessorChanged();
    }
}

bool RecordsModel::busy() const
{
    auto model = qobject_cast<BasicTorrentModel*>(sourceModel());
    if (model) {
        return model->taskRunning();
    }
    return false;
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case ColumnRoles::NaturalIndexRole:
    case ColumnRoles::NameRole:
    case ColumnRoles::TorrentPathRole:
    case ColumnRoles::SavePathRole:
    case ColumnRoles::State:
        return QIdentityProxyModel::data(createIndex(index.row(), columnRoleToSection(role)),
                                         Qt::DisplayRole);
    default:
        return QIdentityProxyModel::data(index, role);
    }
}

QVariant RecordsModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    return QIdentityProxyModel::headerData(section, orientation, role);
}

QList<int> RecordsModel::columnRoles() const
{
    QList<int> list;
    list << ColumnRoles::NaturalIndexRole
         << ColumnRoles::NameRole
         << ColumnRoles::TorrentPathRole
         << ColumnRoles::SavePathRole
         << ColumnRoles::State;
    return list;
}

QByteArray RecordsModel::roleName(int role) const
{
    return roleNames()[role];
}

int RecordsModel::columnRoleToSection(int role) const
{
    switch (role) {
    case ColumnRoles::NaturalIndexRole:
    case ColumnRoles::NameRole:
    case ColumnRoles::TorrentPathRole:
    case ColumnRoles::SavePathRole:
    case ColumnRoles::State:
        return role - Qt::UserRole;
    default:
        return 0;
    }
}

QHash<int, QByteArray> RecordsModel::roleNames() const
{
    auto names = QIdentityProxyModel::roleNames();
    names[ColumnRoles::NaturalIndexRole] = "naturalIndex";
    names[ColumnRoles::NameRole] = "name";
    names[ColumnRoles::TorrentPathRole] = "torrentPath";
    names[ColumnRoles::SavePathRole] = "savePath";
    names[ColumnRoles::State] = "state";
    return names;
}
