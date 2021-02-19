#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unitcrusadecard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(new UnitCrusadeCard(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

