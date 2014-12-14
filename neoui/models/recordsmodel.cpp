#include "recordsmodel.h"
#include "recordsaccessorobject.h"

RecordsModel::RecordsModel(QObject *parent) : QIdentityProxyModel(parent)
{

}

RecordsModel::~RecordsModel()
{
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
        setSourceModel(nullptr);
        delete oldModel;
        if (m_accessor && m_accessor->get()) {
            setSourceModel(new BasicTorrentModel(m_accessor->take(), this));
        }

        emit accessorChanged();
    }
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case ColumnNoRole:
    case ColumnNameRole:
    case ColumnTorrentPathRole:
    case ColumnSavePathRole:
    case ColumnState:
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
    list << ColumnNoRole
         << ColumnNameRole
         << ColumnTorrentPathRole
         << ColumnSavePathRole
         << ColumnState;
    return list;
}

QByteArray RecordsModel::roleName(int role) const
{
    return roleNames()[role];
}

int RecordsModel::columnRoleToSection(int role) const
{
    switch (role) {
    case ColumnNoRole:
    case ColumnNameRole:
    case ColumnTorrentPathRole:
    case ColumnSavePathRole:
    case ColumnState:
        return role - Qt::UserRole;
    default:
        return 0;
    }
}

QHash<int, QByteArray> RecordsModel::roleNames() const
{
    auto names = QIdentityProxyModel::roleNames();
    names[ColumnNoRole] = "columnNo";
    names[ColumnNameRole] = "columnName";
    names[ColumnTorrentPathRole] = "columnTorrentPath";
    names[ColumnSavePathRole] = "columnSavePath";
    names[ColumnState] = "columnState";
    return names;
}
