#include "classiccrusadewindow.h"
#include "ui_classiccrusadewindow.h"

ClassicCrusadeWindow::ClassicCrusadeWindow(OrderOfBattleData * orderOfBattleData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassicCrusadeWindow)
{
    ui->setupUi(this);

    unitCrusadeCard = new UnitCrusadeCard(&orderOfBattleData->units[0], this);
    ui->scrollAreaUnitCard->setWidget(unitCrusadeCard);
    orderOfBattle = new OrderOfBattle(orderOfBattleData, this);
    ui->scrollAreaOrderOfBattle->setWidget(orderOfBattle);

    ConnectLinks();
}

ClassicCrusadeWindow::~ClassicCrusadeWindow()
{
    delete ui;
}

void ClassicCrusadeWindow::SetOrderOfBattleData(OrderOfBattleData *data)
{
    orderOfBattle->SetOrderOfBattleData(data);
}

void ClassicCrusadeWindow::OnDataModified()
{
    DataModified();
}

void ClassicCrusadeWindow::ConnectLinks()
{
    connect(orderOfBattle, &OrderOfBattle::UnitSelected, unitCrusadeCard, &UnitCrusadeCard::OnUnitSelection);
    connect(unitCrusadeCard, &UnitCrusadeCard::DisplayValueChanged, orderOfBattle, &OrderOfBattle::UpdateView);
    connect(orderOfBattle, &OrderOfBattle::DataModified, this, &ClassicCrusadeWindow::OnDataModified);
    connect(unitCrusadeCard, &UnitCrusadeCard::DataModified, this, &ClassicCrusadeWindow::OnDataModified);
}
