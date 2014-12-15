#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QIdentityProxyModel>
#include "basictorrentmodel.h"

class RecordsAccessorObject;

class RecordsModel : public QIdentityProxyModel
{
    Q_OBJECT
    Q_PROPERTY(RecordsAccessorObject *accessor
               READ accessor WRITE setAccessor
               NOTIFY accessorChanged)
    Q_ENUMS(ColumnRoles)
    Q_ENUMS(ColumnCount)
public:
    explicit RecordsModel(QObject *parent = 0);
    ~RecordsModel();

    RecordsAccessorObject *accessor() const;
    void setAccessor(RecordsAccessorObject *accessor);

    Q_INVOKABLE int columnRoleToSection(int role) const;
    Q_INVOKABLE QList<int> columnRoles() const;
    Q_INVOKABLE QByteArray roleName(int role) const;

    Q_INVOKABLE
    virtual QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal,
                                int role = Qt::DisplayRole) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

    enum ColumnRoles {
        ColumnNoRole = Qt::UserRole + BasicTorrentModel::Col_No,
        ColumnNameRole = Qt::UserRole + BasicTorrentModel::Col_Name,
        ColumnTorrentPathRole = Qt::UserRole + BasicTorrentModel::Col_TorrentPath,
        ColumnSavePathRole = Qt::UserRole + BasicTorrentModel::Col_SavePath,
        ColumnState = Qt::UserRole + BasicTorrentModel::Col_State,
    };
    enum ColumnCount {
        ColumnCount = BasicTorrentModel::ColCount
    };

signals:
    void accessorChanged();

private slots:
    void onSourceModelChanged();

private:
    RecordsAccessorObject *m_accessor;
};

#endif // RECORDSMODEL_H
