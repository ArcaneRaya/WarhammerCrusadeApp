#ifndef OOBSORTFILTERPROXYMODEL_H
#define OOBSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <vector>
#include "battlefieldroledata.h"

class OoBSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    OoBSortFilterProxyModel(QObject *parent = 0);
    void SetRoles(std::vector<BattlefieldRoleData> * roles);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    int GetRoleIndex(QString roleString) const;
    std::vector<BattlefieldRoleData> * roles;
};

#endif // OOBSORTFILTERPROXYMODEL_H
