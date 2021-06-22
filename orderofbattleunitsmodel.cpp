#include "orderofbattleunitsmodel.h"

OrderOfBattleUnitsModel::OrderOfBattleUnitsModel(OrderOfBattleData *orderOfBattleData, QObject *parent) : QAbstractItemModel(parent)
{
    this->orderOfBattleData = orderOfBattleData;
}

int OrderOfBattleUnitsModel::rowCount(const QModelIndex &parent) const
{
    return this->orderOfBattleData->units.size();
}

int OrderOfBattleUnitsModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant OrderOfBattleUnitsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole){
        if (index.column() == 0)
        {
            return index.row() + 1;
        }
        if (index.column() == 1)
        {
            return QString::fromStdString(this->orderOfBattleData->units[index.row()].name) +" (" + QString::fromStdString(this->orderOfBattleData->units[index.row()].unitType) + ")";
        }
        if (index.column() == 2)
        {
            return QString::fromStdString(this->orderOfBattleData->units[index.row()].battleFieldRole);
        }
        if (index.column() == 3)
        {
            return QString::number(this->orderOfBattleData->units[index.row()].powerRating);
        }
        if (index.column() == 4)
        {
            return QString::number(this->orderOfBattleData->units[index.row()].crusadePoints);
        }
    }

    return QVariant();
}

QVariant OrderOfBattleUnitsModel::headerData(int section, Qt::Orientation orientation, int role) const {

    QVariant result = QVariant();

    if (Qt::DisplayRole == role && Qt::Horizontal == orientation)
    {
        switch (section) {
            case 0:
            result = "UNIT";
            break;
            case 1:
            result = "UNIT NAME";
            break;
            case 2:
            result = "ROLE";
            break;
            case 3:
            result = "PL";
            break;
            case 4:
            result = "CRP";
            break;
            default:
            break;
        }
    }
    else if (Qt::DisplayRole == role && Qt::Vertical == orientation)
    {
        result = "Unit " + QString::number(section + 1);
    }
    else {

    }
    return result;
}

void OrderOfBattleUnitsModel::sort(int column, Qt::SortOrder order)
{

}

void OrderOfBattleUnitsModel::AddUnit()
{
    beginInsertRows(QModelIndex(), this->orderOfBattleData->units.size() - 1, this->orderOfBattleData->units.size() - 1);
    this->orderOfBattleData->units.push_back(UnitCrusadeData());
    endInsertRows();
}

void OrderOfBattleUnitsModel::RemoveUnit(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    this->orderOfBattleData->units.erase(this->orderOfBattleData->units.begin() + index);
    endRemoveRows();
}

void OrderOfBattleUnitsModel::ReplaceData(OrderOfBattleData *newData)
{
    beginResetModel();
    orderOfBattleData = newData;
    endResetModel();
}

QModelIndex OrderOfBattleUnitsModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column, nullptr);
}

QModelIndex OrderOfBattleUnitsModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

bool OrderOfBattleUnitsModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}
