#ifndef TRANSFORMMODEL_H
#define TRANSFORMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>
#include <QModelIndex>
#include <irecordstransformer.h>

class TransformerModel : public QAbstractListModel
{
public:
    TransformerModel();
    ~TransformerModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    bool insertRow(int row, const QString &name);
    bool removeRow(int row);
    bool moveRow(int from, int to);

    enum RoleNames {
        ArgsRole = Qt::UserRole,
    };

private:
    QList<QVariantMap> argsList;
    QList<QString> nameList;
};

#endif // TRANSFORMMODEL_H
