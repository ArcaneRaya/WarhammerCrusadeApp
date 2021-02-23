#include "orderofbattle.h"
#include "ui_orderofbattle.h"
#include <QMessageBox>

OrderOfBattle::OrderOfBattle(OrderOfBattleData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderOfBattle)
{
    ui->setupUi(this);
    this->data = data;

    model = new OrderOfBattleUnitsModel(data, this);

    ui->tableViewUnits->setModel(model);
    ConnectLinks();

    UpdateView();
    ui->tableViewUnits->resizeColumnsToContents();
}

OrderOfBattle::~OrderOfBattle()
{
    delete ui;
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
    this->data->name = value.toStdString();
}

void OrderOfBattle::OnFactionChanged(QString value)
{
    this->data->faction = value.toStdString();
}

void OrderOfBattle::OnBattleTallyChanged(QString value)
{
    this->data->battleTally = value.toInt();
}

void OrderOfBattle::OnBattlesWonChanged(QString value)
{
    this->data->battlesWon = value.toInt();
}

void OrderOfBattle::OnRequisitionPointsChanged(QString value)
{
    this->data->requisitionPoints = value.toInt();
}

void OrderOfBattle::OnSupplyLimitChanged(QString value)
{
    this->data->supplyLimit = value.toInt();
}

void OrderOfBattle::OnTableItemClicked(const QModelIndex &index)
{
    UnitSelected(&this->data->units[index.row()]);
}

void OrderOfBattle::OnPushButtonAddUnitClicked()
{
    model->AddUnit();
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
