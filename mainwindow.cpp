#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unitcrusadecard.h"
#include "orderofbattle.h"
#include "json.hpp"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->orderOfBattleData = new OrderOfBattleData();
    this->orderOfBattleData->units.push_back(UnitCrusadeData());

    ui->setupUi(this);
    unitCrusadeCard = new UnitCrusadeCard(&this->orderOfBattleData->units[0], this);
    ui->scrollAreaUnitCard->setWidget(unitCrusadeCard);
    orderOfBattle = new OrderOfBattle(this->orderOfBattleData, this);
    ui->scrollAreaOrderOfBattle->setWidget(orderOfBattle);

    connect(orderOfBattle, &OrderOfBattle::UnitSelected, unitCrusadeCard, &UnitCrusadeCard::OnUnitSelection);
    connect(unitCrusadeCard, &UnitCrusadeCard::OnDisplayValueChanged, orderOfBattle, &OrderOfBattle::UpdateView);
}

MainWindow::~MainWindow()
{
    delete this->orderOfBattleData;
    delete ui;
}


void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, QString(), QString(),"JSON files (*.json)");
    if (filePath.isEmpty()){
        ui->statusbar->showMessage("need valid file path");
        return;
    }
    ui->statusbar->showMessage("saving...");
    nlohmann::json json = *this->orderOfBattleData;


    QFile mFile(filePath);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        ui->statusbar->showMessage("could not open for writing");
        return;
    }

    QTextStream out(&mFile);
    QString jsonString = QString::fromStdString(json.dump(4));
    out << jsonString;

    mFile.flush();
    mFile.close();

    ui->statusbar->showMessage("saved");
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, QString(), QString(),"JSON files (*.json)");
    if (filePath.isEmpty()){
        ui->statusbar->showMessage("need valid file path");
        return;
    }
    ui->statusbar->showMessage("loading...");

    QFile mFile(filePath);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        ui->statusbar->showMessage("could not open for reading");
        return;
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();
    mFile.close();

    nlohmann::json json = nlohmann::json::parse(mText.toStdString());
    OrderOfBattleData * datapointer = new OrderOfBattleData();
    json.get_to(*datapointer);

    orderOfBattle->SetOrderOfBattleData(datapointer);

    delete orderOfBattleData;

    orderOfBattleData = datapointer;

    ui->statusbar->showMessage("loaded " + QString::fromStdString(datapointer->units[0].name));
}
