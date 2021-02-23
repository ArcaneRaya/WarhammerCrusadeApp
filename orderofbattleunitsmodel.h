#ifndef ORDEROFBATTLEUNITSMODEL_H
#define ORDEROFBATTLEUNITSMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include "orderofbattledata.h"

class OrderOfBattleUnitsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit OrderOfBattleUnitsModel(OrderOfBattleData *orderOfBattleData, QObject *parent = nullptr);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void AddUnit();
    void ReplaceData(OrderOfBattleData *newData);

private:
    OrderOfBattleData *orderOfBattleData;

signals:

};

#endif // ORDEROFBATTLEUNITSMODEL_H
