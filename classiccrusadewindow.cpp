#include "classiccrusadewindow.h"
#include "ui_classiccrusadewindow.h"

ClassicCrusadeWindow::ClassicCrusadeWindow(RuntimeData * runtimeData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassicCrusadeWindow)
{
    ui->setupUi(this);

    unitCrusadeCard = new UnitCrusadeCard(this);
    ui->scrollAreaUnitCard->setWidget(unitCrusadeCard);
    // TODO: set roles in sort model
    orderOfBattle = new OrderOfBattle(runtimeData, this);
    ui->scrollAreaOrderOfBattle->setWidget(orderOfBattle);

    QStringList battlefieldRoleOptions;
    runtimeData->generalData->GetBattlefieldRolesStringList(&battlefieldRoleOptions);
    unitCrusadeCard->SetBattlefieldRoleOptions(&battlefieldRoleOptions);
    unitCrusadeCard->setVisible(false);

    ConnectLinks();
}

ClassicCrusadeWindow::~ClassicCrusadeWindow()
{
    delete ui;
}

void ClassicCrusadeWindow::SetOrderOfBattleData(RuntimeData *data)
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
