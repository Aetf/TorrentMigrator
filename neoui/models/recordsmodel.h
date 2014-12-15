#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QIdentityProxyModel>
#include "basictorrentmodel.h"

class RecordsAccessorObject;

class ColumnRoles : public QObject
{
    Q_OBJECT
    Q_ENUMS(Roles)
    Q_ENUMS(ColumnCount)
public:
    enum Roles {
        NaturalIndexRole = Qt::UserRole + BasicTorrentModel::Col_No,
        NameRole = Qt::UserRole + BasicTorrentModel::Col_Name,
        TorrentPathRole = Qt::UserRole + BasicTorrentModel::Col_TorrentPath,
        SavePathRole = Qt::UserRole + BasicTorrentModel::Col_SavePath,
        State = Qt::UserRole + BasicTorrentModel::Col_State,
    };
    enum ColumnCount {
        ColumnCount = BasicTorrentModel::ColCount
    };
};

class RecordsModel : public QIdentityProxyModel
{
    Q_OBJECT
    Q_PROPERTY(RecordsAccessorObject *accessor
               READ accessor WRITE setAccessor
               NOTIFY accessorChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_ENUMS(ColumnRoles)
    Q_ENUMS(ColumnCount)
public:
    explicit RecordsModel(QObject *parent = 0);
    ~RecordsModel();

    RecordsAccessorObject *accessor() const;
    void setAccessor(RecordsAccessorObject *accessor);

    bool busy() const;

    Q_INVOKABLE int columnRoleToSection(int role) const;
    Q_INVOKABLE QList<int> columnRoles() const;
    Q_INVOKABLE QByteArray roleName(int role) const;

    Q_INVOKABLE
    virtual QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal,
                                int role = Qt::DisplayRole) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

signals:
    void accessorChanged();
    void busyChanged();

private slots:
    void onSourceModelChanged();

private:
    RecordsAccessorObject *m_accessor;
    bool m_busy;
};

#endif // RECORDSMODEL_H
