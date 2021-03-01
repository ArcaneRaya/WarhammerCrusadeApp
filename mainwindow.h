#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "unitcrusadedata.h"
#include "orderofbattledata.h"
#include "classiccrusadewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;
    ~MainWindow();

private slots:
    void OnActionNewTriggered();
    void OnActionSaveTriggered();
    void OnActionOpenTriggered();

    void OnDataModified();

private:
    const QString APPLICATION_NAME = "CRUSADE EDITOR";

    bool NeedSave();
    void ConnectLinks();

    Ui::MainWindow *ui;
    OrderOfBattleData * orderOfBattleData;
    ClassicCrusadeWindow * classicCrusadeWindow;

    QString filePathCurrentOrderOfBattle;
    bool hasUnsavedChanges;
};
#endif // MAINWINDOW_H
