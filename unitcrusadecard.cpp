#include "unitcrusadecard.h"
#include "ui_unitcrusadecard.h"

UnitCrusadeCard::UnitCrusadeCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitCrusadeCard)
{
    ui->setupUi(this);
    ui->comboBoxRank->installEventFilter(this);
    ui->comboBoxRole->installEventFilter(this);
}

UnitCrusadeCard::~UnitCrusadeCard()
{
    delete ui;
}

bool UnitCrusadeCard::eventFilter(QObject *targetQObject, QEvent *currentEvent)
{
    if ((targetQObject == ui->comboBoxRank || targetQObject == ui->comboBoxRole) && currentEvent->type() == QEvent::Wheel)
    {
            return true;
    }
    return QObject::eventFilter(targetQObject, currentEvent);
}
