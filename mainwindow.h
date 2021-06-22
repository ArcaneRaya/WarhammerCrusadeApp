#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTimer>
#include "unitcrusadedata.h"
#include "orderofbattledata.h"
#include "classiccrusadewindow.h"
#include "runtimedata.h"

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
    void OnActionSaveAsTriggered();
    void OnActionOpenTriggered();
    void AutoSave();
    void SaveUsingPath(QString path);

    void OnDataModified();

private:
    const QString APPLICATION_NAME = "CRUSADE EDITOR";

    bool NeedSave();
    void ConnectLinks();
    void LoadRuntimeData();

    QTimer *autosaveTimer;
    Ui::MainWindow *ui;
    ClassicCrusadeWindow * classicCrusadeWindow;
    RuntimeData * runtimeData;
};
#endif // MAINWINDOW_H
