#ifndef UNITCRUSADECARD_H
#define UNITCRUSADECARD_H

#include <QWidget>

#include "unitcrusadedata.h"

namespace Ui {
class UnitCrusadeCard;
}

class UnitCrusadeCard : public QWidget
{
    Q_OBJECT

public:
    explicit UnitCrusadeCard(UnitCrusadeData *data, QWidget *parent = nullptr);
    ~UnitCrusadeCard();

    bool eventFilter(QObject *o, QEvent *ev);

signals:
    void OnDisplayValueChanged();

public slots:
    void OnUnitSelection(UnitCrusadeData *unit);

private slots:
    void OnNameChanged(QString value);
    void OnBattleFieldRoleChanged(QString value);

private:
    void UpdateView();
    void ConnectLinks();
    Ui::UnitCrusadeCard *ui;
    UnitCrusadeData *data;
};

#endif // UNITCRUSADECARD_H
