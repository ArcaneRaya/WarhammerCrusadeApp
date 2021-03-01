#ifndef ORDEROFBATTLE_H
#define ORDEROFBATTLE_H

#include <QWidget>
#include "orderofbattledata.h"
#include "orderofbattleunitsmodel.h"

namespace Ui {
class OrderOfBattle;
}

class OrderOfBattle : public QWidget
{
    Q_OBJECT

public:
    explicit OrderOfBattle(OrderOfBattleData *data, QWidget *parent = nullptr);
    ~OrderOfBattle();
    void SetOrderOfBattleData(OrderOfBattleData *data);

signals:
    void UnitSelected(UnitCrusadeData *unit);
    void DataModified();

public slots:
    void UpdateView();

private:
    void ConnectLinks();
    Ui::OrderOfBattle *ui;
    OrderOfBattleData *data;
    OrderOfBattleUnitsModel *model ;
    int currentSelectedRow;

private slots:
    void OnNameChanged(QString value);
    void OnFactionChanged(QString value);

    void OnBattleTallyChanged(QString value);
    void OnBattlesWonChanged(QString value);
    void OnRequisitionPointsChanged(QString value);
    void OnSupplyLimitChanged(QString value);

    void OnTableItemClicked(const QModelIndex &index);

    void OnPushButtonAddUnitClicked();
    void OnPushButtonRemoveSelectedUnitclicked();
};

#endif // ORDEROFBATTLE_H
