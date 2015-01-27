#include "transformermodel.h"

TransformerModel::TransformerModel()
{

}

TransformerModel::~TransformerModel()
{
}

int TransformerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return nameList.length();
}

QHash<int, QByteArray> TransformerModel::roleNames() const
{
    auto hash = QAbstractListModel::roleNames();
    hash[ArgsRole] = "args";

    return hash;
}

QVariant TransformerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) { return QVariant(); }

    switch (role) {
    case ArgsRole:
        return argsList.at(index.row());
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
    beginInsertRows(QModelIndex(), row, row);
    nameList.insert(row, name);
    argsList.insert(row, QVariantMap());
    endInsertRows();

    return true;
}

bool TransformerModel::removeRow(int row)
{
    if (row < 0 || row >= nameList.length()) { return false; }

    beginRemoveRows(QModelIndex(), row, row);
    nameList.removeAt(row);
    argsList.removeAt(row);
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
    endMoveRows();

    return true;
}
