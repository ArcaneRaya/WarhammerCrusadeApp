#include "orderofbattle.h"
#include "ui_orderofbattle.h"
#include <QMessageBox>

OrderOfBattle::OrderOfBattle(RuntimeData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderOfBattle)
{
    ui->setupUi(this);
    model = new OrderOfBattleUnitsModel(data->orderOfBattleData, this);
    sortModel = new OoBSortFilterProxyModel(this);
    sortModel->setSourceModel(model);
    sortModel->SetRoles(&data->generalData->roles);
    ui->tableViewUnits->setModel(sortModel);

    ConnectLinks();
    SetOrderOfBattleData(data);
    currentSelectedRow = 0;
}

OrderOfBattle::~OrderOfBattle()
{
    delete ui;
}

void OrderOfBattle::SetOrderOfBattleData(RuntimeData *newData)
{
    this->data = newData;
    model->ReplaceData(data->orderOfBattleData);

    UpdateView();

    ui->tableViewUnits->resizeColumnsToContents();

    if (data->orderOfBattleData->units.size() > 0){
        UnitSelected(&data->orderOfBattleData->units[0]);
    } else {
        UnitSelected(nullptr);
    }
}

void OrderOfBattle::UpdateView()
{
    ui->lineEditName->setText(QString::fromStdString(data->orderOfBattleData->name));
    ui->lineEditFaction->setText(QString::fromStdString(data->orderOfBattleData->faction));

    ui->lineEditBattleTallyAmount->setText(QString::number(data->orderOfBattleData->battleTally));
    ui->lineEditBattlesWonAmount->setText(QString::number(data->orderOfBattleData->battlesWon));
    ui->lineEditRequisitionPointsAmount->setText(QString::number(data->orderOfBattleData->requisitionPoints));
    ui->lineEditSupplyLimitAmount->setText(QString::number(data->orderOfBattleData->supplyLimit));

    int supplyUsed = 0;
    for(auto unit : data->orderOfBattleData->units){
        supplyUsed += unit.powerRating;
    }
    ui->labelSupplyUsedAmount->setText(QString::number(supplyUsed));

    ui->tableViewUnits->update();
    ui->tableViewUnits->viewport()->update();
}

void OrderOfBattle::OnNameChanged(QString value)
{
    data->orderOfBattleData->name = value.toStdString();
    DataModified();
}

void OrderOfBattle::OnFactionChanged(QString value)
{
    data->orderOfBattleData->faction = value.toStdString();
    DataModified();
}

void OrderOfBattle::OnBattleTallyChanged(QString value)
{
    data->orderOfBattleData->battleTally = value.toInt();
    DataModified();
}

void OrderOfBattle::OnBattlesWonChanged(QString value)
{
    data->orderOfBattleData->battlesWon = value.toInt();
    DataModified();
}

void OrderOfBattle::OnRequisitionPointsChanged(QString value)
{
    data->orderOfBattleData->requisitionPoints = value.toInt();
    DataModified();
}

void OrderOfBattle::OnSupplyLimitChanged(QString value)
{
    data->orderOfBattleData->supplyLimit = value.toInt();
    DataModified();
}

void OrderOfBattle::OnTableItemClicked(const QModelIndex &index)
{
    currentSelectedRow = sortModel->mapToSource(index).row();
    UnitSelected(&data->orderOfBattleData->units[currentSelectedRow]);
}

void OrderOfBattle::OnPushButtonAddUnitClicked()
{
    model->AddUnit();
    currentSelectedRow = data->orderOfBattleData->units.size()-1;
    QModelIndex index = model->index(currentSelectedRow, 0, QModelIndex());
    ui->tableViewUnits->selectRow(sortModel->mapFromSource(index).row());
    UnitSelected(&data->orderOfBattleData->units[currentSelectedRow]);
    DataModified();
}

void OrderOfBattle::OnPushButtonRemoveSelectedUnitclicked()
{
    if (data->orderOfBattleData->units.size() <= 1){
        QMessageBox::warning(this, "Last Unit", "Cannot remove last unit in Order of Battle");
        return;
    }

    QMessageBox messageBoxRemovalWarning;
    messageBoxRemovalWarning.setIcon(QMessageBox::Warning);
    messageBoxRemovalWarning.setWindowTitle("Unit Removal: " + QString::fromStdString(data->orderOfBattleData->units[currentSelectedRow].name));
    messageBoxRemovalWarning.setText("Are you sure you want to remove this unit? This action cannot be undone.");
    messageBoxRemovalWarning.addButton("Remove Unit", QMessageBox::YesRole);
    messageBoxRemovalWarning.addButton("Cancel", QMessageBox::NoRole);
    messageBoxRemovalWarning.exec();

    if(messageBoxRemovalWarning.buttonRole(messageBoxRemovalWarning.clickedButton()) == QMessageBox::NoRole){
        return;
    }

    if (currentSelectedRow == 0){
        UnitSelected(&data->orderOfBattleData->units[1]);
    } else {
        UnitSelected(&data->orderOfBattleData->units[0]);
    }

    model->RemoveUnit(currentSelectedRow);

    currentSelectedRow = 0;
    QModelIndex index = model->index(currentSelectedRow, 0, QModelIndex());
    ui->tableViewUnits->selectRow(sortModel->mapFromSource(index).row());
    UnitSelected(&data->orderOfBattleData->units[currentSelectedRow]);
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
