#ifndef CLASSICCRUSADEWINDOW_H
#define CLASSICCRUSADEWINDOW_H

#include <QWidget>
#include "orderofbattledata.h"
#include "orderofbattle.h"
#include "unitcrusadecard.h"

namespace Ui {
class ClassicCrusadeWindow;
}

class ClassicCrusadeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClassicCrusadeWindow(OrderOfBattleData * orderOfBattleData, QWidget *parent = nullptr);
    ~ClassicCrusadeWindow();

    void SetOrderOfBattleData(OrderOfBattleData * data);

signals:
    void DataModified();

private slots:
    void OnDataModified();

private:
    void ConnectLinks();

    Ui::ClassicCrusadeWindow *ui;
    OrderOfBattle * orderOfBattle;
    UnitCrusadeCard * unitCrusadeCard;
};

#endif // CLASSICCRUSADEWINDOW_H
