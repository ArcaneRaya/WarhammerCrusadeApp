#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unitcrusadecard.h"
#include "json.hpp"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->unitCrusadeData = new UnitCrusadeData();
    this->unitCrusadeData->name = "Assigned name";

    ui->setupUi(this);
    ui->scrollAreaUnitCard->setWidget(new UnitCrusadeCard(this->unitCrusadeData, this));
}

MainWindow::~MainWindow()
{
    delete this->unitCrusadeData;
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
    nlohmann::json json = *this->unitCrusadeData;


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
    UnitCrusadeData loadedData = json.get<UnitCrusadeData>();

    ui->statusbar->showMessage("saved");
}
