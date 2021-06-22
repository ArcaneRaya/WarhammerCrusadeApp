#include "oobsortfilterproxymodel.h"

OoBSortFilterProxyModel::OoBSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void OoBSortFilterProxyModel::SetRoles(std::vector<BattlefieldRoleData> *roles)
{
    this->roles = roles;
}

bool OoBSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    return true;
}

bool OoBSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    switch (left.column()) {
    case 1: // Unit Name
        return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0;
    case 2: // Role
        return GetRoleIndex(leftData.toString()) < GetRoleIndex(rightData.toString());
    case 3: // Power Level
        return leftData.toInt() < rightData.toInt();
    case 4: // Crusade Points
        return leftData.toInt() < rightData.toInt();
    case 0: // Unit Index
    default:
        return left.row() < right.row();
    }
}

int OoBSortFilterProxyModel::GetRoleIndex(QString roleString) const
{
    int somevalue = 0;
    for(int i = 0; i < roles->size(); i++){
        if (QString::fromStdString((*roles)[i].name) == roleString){
            return (*roles)[i].index;
        }
    }
    return -1;
}

