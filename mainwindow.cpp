#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unitcrusadecard.h"
#include "orderofbattle.h"
#include "json.hpp"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAbstractButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    orderOfBattleData = new OrderOfBattleData();
    orderOfBattleData->units.push_back(UnitCrusadeData());

    ui->setupUi(this);

    classicCrusadeWindow = new ClassicCrusadeWindow(orderOfBattleData, this);

    ui->tabWidget->addTab(classicCrusadeWindow, "Classic");

    ConnectLinks();

    setWindowTitle(APPLICATION_NAME + " - " + QString::fromStdString(orderOfBattleData->name));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (hasUnsavedChanges){
        QMessageBox closeWithUnsavedChangesWarning;
        closeWithUnsavedChangesWarning.setIcon(QMessageBox::Warning);
        closeWithUnsavedChangesWarning.setWindowTitle("Unsaved Changes");
        closeWithUnsavedChangesWarning.setText("You have unsaved changes, are you sure you want to quit?");
        closeWithUnsavedChangesWarning.addButton("Quit", QMessageBox::YesRole);
        closeWithUnsavedChangesWarning.addButton("Cancel", QMessageBox::NoRole);
        closeWithUnsavedChangesWarning.exec();

        if(closeWithUnsavedChangesWarning.buttonRole(closeWithUnsavedChangesWarning.clickedButton()) == QMessageBox::NoRole){
            event->ignore();
            return;
        }
    }

    event->accept();
}

MainWindow::~MainWindow()
{
    delete this->orderOfBattleData;
    delete ui;
}

void MainWindow::OnActionNewTriggered()
{
    if(NeedSave()){
        return;
    }


    OrderOfBattleData * datapointer = new OrderOfBattleData();
    datapointer->units.push_back(UnitCrusadeData());

    classicCrusadeWindow->SetOrderOfBattleData(datapointer);

    delete orderOfBattleData;

    orderOfBattleData = datapointer;

    filePathCurrentOrderOfBattle = "";

    ui->statusbar->showMessage("New Order of Battle Created");
}


void MainWindow::OnActionSaveTriggered()
{
    if(filePathCurrentOrderOfBattle.isEmpty()){
        filePathCurrentOrderOfBattle = QFileDialog::getSaveFileName(this, QString(), QString(),"JSON files (*.json)");
    }

    if (filePathCurrentOrderOfBattle.isEmpty()){
        ui->statusbar->showMessage("need valid file path");
        QMessageBox::warning(this, "Invalid Path", "Provided path is invalid, cannot save");
        return;
    }

    ui->statusbar->showMessage("saving...");
    nlohmann::json json = *this->orderOfBattleData;


    QFile mFile(filePathCurrentOrderOfBattle);
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

    hasUnsavedChanges = false;

    setWindowTitle(APPLICATION_NAME + " - " + QString::fromStdString(orderOfBattleData->name));

    ui->statusbar->showMessage("saved");
}

void MainWindow::OnActionOpenTriggered()
{
    if(NeedSave()){
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(this, QString(), QString(),"JSON files (*.json)");
    if (filePath.isEmpty()){
        ui->statusbar->showMessage("need valid file path");
        QMessageBox::warning(this, "Invalid Path", "Provided path is invalid, cannot open");
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

    classicCrusadeWindow->SetOrderOfBattleData(datapointer);

    delete orderOfBattleData;

    orderOfBattleData = datapointer;

    filePathCurrentOrderOfBattle = filePath;

    ui->statusbar->showMessage("loaded " + QString::fromStdString(datapointer->name));
}

bool MainWindow::NeedSave()
{
    if (hasUnsavedChanges)
    {
        ui->statusbar->showMessage("Order of Battle has unsaved changes");
        QMessageBox messageBoxUnsavedChanges;
        messageBoxUnsavedChanges.setIcon(QMessageBox::Warning);
        messageBoxUnsavedChanges.setWindowTitle("Unsaved Changes");
        messageBoxUnsavedChanges.setText("Current Order of Battle has unsaved changes. Do you want to discard these changes and continue?");
        messageBoxUnsavedChanges.addButton("Discard and Continue", QMessageBox::YesRole);
        messageBoxUnsavedChanges.addButton("Cancel", QMessageBox::NoRole);
        messageBoxUnsavedChanges.exec();

        if(messageBoxUnsavedChanges.buttonRole(messageBoxUnsavedChanges.clickedButton()) == QMessageBox::NoRole){
            return true;
        }
    }

    return false;
}

void MainWindow::ConnectLinks()
{
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::OnActionNewTriggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::OnActionSaveTriggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OnActionOpenTriggered);

    connect(classicCrusadeWindow, &ClassicCrusadeWindow::DataModified, this, &MainWindow::OnDataModified);
}

void MainWindow::OnDataModified()
{
    hasUnsavedChanges = true;
    setWindowTitle(APPLICATION_NAME + " - " + QString::fromStdString(orderOfBattleData->name) + "*");
    ui->statusbar->showMessage("data modified");
}
