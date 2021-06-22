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
    ui->setupUi(this);

    LoadRuntimeData();

    classicCrusadeWindow = new ClassicCrusadeWindow(runtimeData, this);

    ui->tabWidget->addTab(classicCrusadeWindow, "Classic");

    ConnectLinks();

    setWindowTitle(APPLICATION_NAME + " - " + QString::fromStdString(runtimeData->orderOfBattleData->name));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (runtimeData->currentOrderOfBattleHasUnsavedChanges){
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
    delete this->runtimeData->generalData;
    delete this->runtimeData->orderOfBattleData;
    delete this->runtimeData;
    delete ui;
}

void MainWindow::OnActionNewTriggered()
{
    if(NeedSave()){
        return;
    }

    OrderOfBattleData * previousOrderOfBattle = runtimeData->orderOfBattleData;
    runtimeData->orderOfBattleData = new OrderOfBattleData();
    runtimeData->orderOfBattleData->units.push_back(UnitCrusadeData());

    classicCrusadeWindow->SetOrderOfBattleData(runtimeData);

    delete previousOrderOfBattle;

    runtimeData->filePathCurrentOrderOfBattle = "";

    ui->statusbar->showMessage("New Order of Battle Created");
}


void MainWindow::OnActionSaveTriggered()
{
    if(runtimeData->filePathCurrentOrderOfBattle.isEmpty()){
        runtimeData->filePathCurrentOrderOfBattle = QFileDialog::getSaveFileName(this, QString(), QString(),"Order of Battle files (*.OoB)");
    }

    SaveUsingPath(runtimeData->filePathCurrentOrderOfBattle);
}

void MainWindow::OnActionSaveAsTriggered()
{
    QString queriedPath = QFileDialog::getSaveFileName(this, QString(), QString(),"Order of Battle files (*.OoB)");

    if (queriedPath.isEmpty()){
        ui->statusbar->showMessage("need valid file path");
        QMessageBox::warning(this, "Invalid Path", "Provided path is invalid, cannot save");
        return;
    }

    runtimeData->filePathCurrentOrderOfBattle = queriedPath;

    SaveUsingPath(runtimeData->filePathCurrentOrderOfBattle);
}

void MainWindow::OnActionOpenTriggered()
{
    if(NeedSave()){
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(this, QString(), QString(),"Order of Battle files (*.OoB *Json)");
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

    OrderOfBattleData * previousOrderOfBattleData = runtimeData->orderOfBattleData;
    runtimeData->orderOfBattleData = new OrderOfBattleData();
    json.get_to(*runtimeData->orderOfBattleData);

    classicCrusadeWindow->SetOrderOfBattleData(runtimeData);

    delete previousOrderOfBattleData;

    runtimeData->filePathCurrentOrderOfBattle = filePath;

    ui->statusbar->showMessage("loaded " + QString::fromStdString(runtimeData->orderOfBattleData->name));
}

void MainWindow::SaveUsingPath(QString path)
{
    if (path.isEmpty()){
        ui->statusbar->showMessage("need valid file path");
        QMessageBox::warning(this, "Invalid Path", "Provided path is invalid, cannot save");
        return;
    }

    ui->statusbar->showMessage("saving...");
    nlohmann::json json = *this->runtimeData->orderOfBattleData;


    QFile mFile(path);
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

    runtimeData->currentOrderOfBattleHasUnsavedChanges = false;

    setWindowTitle(APPLICATION_NAME + " - " + QString::fromStdString(runtimeData->orderOfBattleData->name));

    ui->statusbar->showMessage("saved");
}

bool MainWindow::NeedSave()
{
    if (runtimeData->currentOrderOfBattleHasUnsavedChanges)
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
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::OnActionSaveAsTriggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OnActionOpenTriggered);

    connect(classicCrusadeWindow, &ClassicCrusadeWindow::DataModified, this, &MainWindow::OnDataModified);
}

void MainWindow::LoadRuntimeData()
{
    runtimeData = new RuntimeData();
    runtimeData->generalData = new GeneralCrusadeData();

    runtimeData->orderOfBattleData = new OrderOfBattleData();
    runtimeData->orderOfBattleData->units.push_back(UnitCrusadeData());

    QString generalDataFilePath = ":/data/generalData.json";

    QFile mFile(generalDataFilePath);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        ui->statusbar->showMessage("could not open general data file for reading");
        return;
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();
    mFile.close();

    nlohmann::json json = nlohmann::json::parse(mText.toStdString());
    json.get_to(*runtimeData->generalData);

    ui->statusbar->showMessage("loaded general data");
}

void MainWindow::OnDataModified()
{
    runtimeData->currentOrderOfBattleHasUnsavedChanges = true;
    setWindowTitle(APPLICATION_NAME + " - " + QString::fromStdString(runtimeData->orderOfBattleData->name) + "*");
    ui->statusbar->showMessage("data modified");
}
