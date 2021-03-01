#include "orderofbattle.h"
#include "ui_orderofbattle.h"
#include <QMessageBox>

OrderOfBattle::OrderOfBattle(OrderOfBattleData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderOfBattle)
{
    ui->setupUi(this);
    model = new OrderOfBattleUnitsModel(data, this);
    ui->tableViewUnits->setModel(model);

    ConnectLinks();
    SetOrderOfBattleData(data);
    currentSelectedRow = 0;
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
    DataModified();
}

void OrderOfBattle::OnFactionChanged(QString value)
{
    data->faction = value.toStdString();
    DataModified();
}

void OrderOfBattle::OnBattleTallyChanged(QString value)
{
    data->battleTally = value.toInt();
    DataModified();
}

void OrderOfBattle::OnBattlesWonChanged(QString value)
{
    data->battlesWon = value.toInt();
    DataModified();
}

void OrderOfBattle::OnRequisitionPointsChanged(QString value)
{
    data->requisitionPoints = value.toInt();
    DataModified();
}

void OrderOfBattle::OnSupplyLimitChanged(QString value)
{
    data->supplyLimit = value.toInt();
    DataModified();
}

void OrderOfBattle::OnTableItemClicked(const QModelIndex &index)
{
    currentSelectedRow = index.row();
    UnitSelected(&this->data->units[currentSelectedRow]);
}

void OrderOfBattle::OnPushButtonAddUnitClicked()
{
    model->AddUnit();
    currentSelectedRow = data->units.size()-1;
    ui->tableViewUnits->selectRow(currentSelectedRow);
    UnitSelected(&data->units[currentSelectedRow]);
    DataModified();
}

void OrderOfBattle::OnPushButtonRemoveSelectedUnitclicked()
{
    if (data->units.size() <= 1){
        QMessageBox::warning(this, "Last Unit", "Cannot remove last unit in Order of Battle");
        return;
    }

    QMessageBox messageBoxRemovalWarning;
    messageBoxRemovalWarning.setIcon(QMessageBox::Warning);
    messageBoxRemovalWarning.setWindowTitle("Unit Removal: " + QString::fromStdString(data->units[currentSelectedRow].name));
    messageBoxRemovalWarning.setText("Are you sure you want to remove this unit? This action cannot be undone.");
    messageBoxRemovalWarning.addButton("Remove Unit", QMessageBox::YesRole);
    messageBoxRemovalWarning.addButton("Cancel", QMessageBox::NoRole);
    messageBoxRemovalWarning.exec();

    if(messageBoxRemovalWarning.buttonRole(messageBoxRemovalWarning.clickedButton()) == QMessageBox::NoRole){
        return;
    }

    if (currentSelectedRow == 0){
        UnitSelected(&data->units[1]);
    } else {
        UnitSelected(&data->units[0]);
    }

    model->RemoveUnit(currentSelectedRow);

    currentSelectedRow = 0;
    ui->tableViewUnits->selectRow(currentSelectedRow);
    UnitSelected(&data->units[currentSelectedRow]);
    DataModified();
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
    connect(ui->pushButtonRemoveSelectedUnit, &QPushButton::clicked, this, &OrderOfBattle::OnPushButtonRemoveSelectedUnitclicked);
}
