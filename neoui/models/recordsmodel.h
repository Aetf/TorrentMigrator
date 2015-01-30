#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QIdentityProxyModel>
#include "basictorrentmodel.h"
#include "recordsaccessorfactory.h"

class ColumnRoles : public QObject
{
    Q_OBJECT
    Q_ENUMS(Roles)
    Q_ENUMS(ColumnCount)
public:
    enum Roles {
        NaturalIndexRole = BasicTorrentModel::UnusedRole + BasicTorrentModel::Col_No,
        NameRole = BasicTorrentModel::UnusedRole + BasicTorrentModel::Col_Name,
        TorrentPathRole =BasicTorrentModel::UnusedRole + BasicTorrentModel::Col_TorrentPath,
        SavePathRole = BasicTorrentModel::UnusedRole + BasicTorrentModel::Col_SavePath,
        State = BasicTorrentModel::UnusedRole + BasicTorrentModel::Col_State,
    };
    enum ColumnCount {
        ColumnCount = BasicTorrentModel::ColCount
    };
};

class RecordsModel : public QIdentityProxyModel
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_ENUMS(ColumnRoles)
    Q_ENUMS(ColumnCount)
public:
    explicit RecordsModel(QObject *parent = nullptr);
    ~RecordsModel();

    bool busy() const;

    Q_INVOKABLE
    void setAccessor(const QString &name, const QVariantMap &args);

    Q_INVOKABLE int columnRoleToSection(int role) const;
    Q_INVOKABLE QList<int> columnRoles() const;
    Q_INVOKABLE QByteArray roleName(int role) const;

    Q_INVOKABLE
    virtual QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal,
                                int role = Qt::DisplayRole) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

signals:
    void busyChanged();

private slots:
    void onSourceModelChanged();

private:
    bool m_busy;
};

#endif // RECORDSMODEL_H
