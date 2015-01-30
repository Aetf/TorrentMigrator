#include "transformermodel.h"

TransformerModel::TransformerModel(QObject *parent)
    : QAbstractListModel(parent)
{ }

TransformerModel::~TransformerModel()
{ }

int TransformerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return nameList.length();
}

QHash<int, QByteArray> TransformerModel::roleNames() const
{
    auto hash = QAbstractListModel::roleNames();
    hash[ArgsRole] = "args";
    hash[ArgsStrRole] = "argsStr";
    hash[Qt::DisplayRole] = "name";

    return hash;
}

QVariant TransformerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) { return QVariant(); }

    switch (role) {
    case ArgsRole:
        return argsList.at(index.row());
    case ArgsStrRole:
        return argsStrList.at(index.row());
    case Qt::DisplayRole:
        return nameList.at(index.row());
    }

    return QVariant();
}

bool TransformerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) { return false; }

    switch (role) {
    case ArgsRole:
        if (value.canConvert<QVariantMap>()) {
            argsList[index.row()] = value.toMap();
            return true;
        }
        break;
    case ArgsStrRole:
        if (value.canConvert<QString>()) {
            argsStrList[index.row()] = value.toString();
            return true;
        }
        break;
    case Qt::DisplayRole:
        if (value.canConvert<QString>()) {
            nameList[index.row()] = value.toString();
            return true;
        }
        break;
    }

    return false;
}

bool TransformerModel::insertRow(int row, const QString &name)
{
    if (row == -1) { row = rowCount(); }
    beginInsertRows(QModelIndex(), row, row);
    nameList.insert(row, name);
    argsList.insert(row, QVariantMap());
    argsStrList.insert(row, QString());
    endInsertRows();

    return true;
}

bool TransformerModel::removeRow(int row)
{
    if (row < 0 || row >= nameList.length()) { return false; }

    beginRemoveRows(QModelIndex(), row, row);
    nameList.removeAt(row);
    argsList.removeAt(row);
    argsStrList.removeAt(row);
    endRemoveRows();

    return true;
}

bool TransformerModel::moveRow(int from, int to)
{
    if (from < 0 || from >= rowCount()) { return false; }
    if (to < 0
        || to >= rowCount()
        || to == from) {
        return false;
    }

    beginMoveRows(QModelIndex(), from, from, QModelIndex(),
                  to < from ? to : to + 1);

    nameList.move(from, to);
    argsList.move(from, to);
    argsStrList.move(from, to);
    endMoveRows();

    return true;
}
