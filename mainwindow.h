#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "macro.h"
#include "custom.h"
#include "scene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
       ~MainWindow();
signals:
private:

    MenuBar* menuBar = nullptr;
    ChooseLevelScene* levelScene = nullptr;
    MainScene* mainScene = nullptr;
    PlayScene* playScene = nullptr;
public slots:
    void RepSceneFucn(int code);

};

#endif // MAINWINDOW_H
