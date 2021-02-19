#include "unitcrusadecard.h"
#include "ui_unitcrusadecard.h"

UnitCrusadeCard::UnitCrusadeCard(UnitCrusadeData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitCrusadeCard)
{
    ui->setupUi(this);
    ui->comboBoxRank->installEventFilter(this);
    ui->comboBoxRole->installEventFilter(this);

    this->data = data;

    UpdateView();
    ConnectLinks();
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

void UnitCrusadeCard::OnUnitSelection(UnitCrusadeData *unit)
{
    this->data = unit;
    UpdateView();
}

void UnitCrusadeCard::OnNameChanged(QString value)
{
    this->data->name = value.toStdString();
    this->OnDisplayValueChanged();
}

void UnitCrusadeCard::OnBattleFieldRoleChanged(QString value)
{
    this->data->battleFieldRole = value.toStdString();
    this->OnDisplayValueChanged();
}

void UnitCrusadeCard::UpdateView()
{
    ui->lineEditName->setText(QString::fromStdString(data->name));
    if (data->battleFieldRole.empty() == false){
        ui->comboBoxRole->setCurrentText(QString::fromStdString(data->battleFieldRole));
    }
}

void UnitCrusadeCard::ConnectLinks()
{
    connect(ui->lineEditName, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnNameChanged);
    connect(ui->comboBoxRole, &QComboBox::currentTextChanged, this, &UnitCrusadeCard::OnBattleFieldRoleChanged);
}
