#include "orderofbattle.h"
#include "ui_orderofbattle.h"
#include <QMessageBox>

OrderOfBattle::OrderOfBattle(OrderOfBattleData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderOfBattle)
{
    ui->setupUi(this);
    model = new OrderOfBattleUnitsModel(data, this);

    ConnectLinks();
    SetOrderOfBattleData(data);

    ui->tableViewUnits->setModel(model);
}

OrderOfBattle::~OrderOfBattle()
{
    delete ui;
}

void OrderOfBattle::SetOrderOfBattleData(OrderOfBattleData *newData)
{
    this->data = newData;
    model->ReplaceData(data);

    UpdateView();

    ui->tableViewUnits->resizeColumnsToContents();

    if (data->units.size() > 0){
        UnitSelected(&data->units[0]);
    }
}

void OrderOfBattle::UpdateView()
{
    ui->lineEditName->setText(QString::fromStdString(this->data->name));
    ui->lineEditFaction->setText(QString::fromStdString(this->data->faction));

    ui->lineEditBattleTallyAmount->setText(QString::number(this->data->battleTally));
    ui->lineEditBattlesWonAmount->setText(QString::number(this->data->battlesWon));
    ui->lineEditRequisitionPointsAmount->setText(QString::number(this->data->requisitionPoints));
    ui->lineEditSupplyLimitAmount->setText(QString::number(this->data->supplyLimit));

    int supplyUsed = 0;
    for(auto unit : this->data->units){
        supplyUsed += unit.powerRating;
    }
    ui->labelSupplyUsedAmount->setText(QString::number(supplyUsed));

    ui->tableViewUnits->update();
    ui->tableViewUnits->viewport()->update();
}

void OrderOfBattle::OnNameChanged(QString value)
{
    data->name = value.toStdString();
    data->SetUnsaved();
}

void OrderOfBattle::OnFactionChanged(QString value)
{
    data->faction = value.toStdString();
    data->SetUnsaved();
}

void OrderOfBattle::OnBattleTallyChanged(QString value)
{
    data->battleTally = value.toInt();
    data->SetUnsaved();
}

void OrderOfBattle::OnBattlesWonChanged(QString value)
{
    data->battlesWon = value.toInt();
    data->SetUnsaved();
}

void OrderOfBattle::OnRequisitionPointsChanged(QString value)
{
    data->requisitionPoints = value.toInt();
    data->SetUnsaved();
}

void OrderOfBattle::OnSupplyLimitChanged(QString value)
{
    data->supplyLimit = value.toInt();
    data->SetUnsaved();
}

void OrderOfBattle::OnTableItemClicked(const QModelIndex &index)
{
    UnitSelected(&this->data->units[index.row()]);
}

void OrderOfBattle::OnPushButtonAddUnitClicked()
{
    model->AddUnit();
    UnitSelected(&data->units[data->units.size()-1]);
}

void OrderOfBattle::ConnectLinks()
{
    connect(ui->lineEditName, &QLineEdit::textChanged, this, &OrderOfBattle::OnNameChanged);
    connect(ui->lineEditFaction, &QLineEdit::textChanged, this, &OrderOfBattle::OnFactionChanged);

    connect(ui->lineEditBattleTallyAmount, &IntValueLineEdit::textChanged, this, &OrderOfBattle::OnBattleTallyChanged);
    connect(ui->lineEditBattlesWonAmount, &IntValueLineEdit::textChanged, this, &OrderOfBattle::OnBattlesWonChanged);
    connect(ui->lineEditRequisitionPointsAmount, &IntValueLineEdit::textChanged, this, &OrderOfBattle::OnRequisitionPointsChanged);
    connect(ui->lineEditSupplyLimitAmount, &IntValueLineEdit::textChanged, this, &OrderOfBattle::OnSupplyLimitChanged);

    connect(ui->tableViewUnits, &QTableView::clicked, this, &OrderOfBattle::OnTableItemClicked);

    connect(ui->pushButtonAddUnit, &QPushButton::clicked, this, &OrderOfBattle::OnPushButtonAddUnitClicked);
}
