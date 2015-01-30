#ifndef TRANSFORMMODEL_H
#define TRANSFORMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>
#include <QModelIndex>
#include <irecordstransformer.h>

class TransformerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TransformerModel(QObject *parent = nullptr);
    ~TransformerModel();

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE bool insertRow(int row, const QString &name);
    Q_INVOKABLE bool removeRow(int row);
    Q_INVOKABLE bool moveRow(int from, int to);

    enum RoleNames {
        ArgsRole = Qt::UserRole,
        ArgsStrRole
    };

private:
    QList<QVariantMap> argsList;
    QList<QString> argsStrList;
    QList<QString> nameList;
};

#endif // TRANSFORMMODEL_H
