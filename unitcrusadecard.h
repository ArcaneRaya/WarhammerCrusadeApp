#ifndef UNITCRUSADECARD_H
#define UNITCRUSADECARD_H

#include <QWidget>

namespace Ui {
class UnitCrusadeCard;
}

class UnitCrusadeCard : public QWidget
{
    Q_OBJECT

public:
    explicit UnitCrusadeCard(QWidget *parent = nullptr);
    ~UnitCrusadeCard();

    bool eventFilter(QObject *o, QEvent *ev);

private:
    Ui::UnitCrusadeCard *ui;
};

#endif // UNITCRUSADECARD_H
