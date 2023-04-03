#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(MAIN_SCENE_WINDOW_W,MAIN_SCENE_WINDOW_H);
    this->setWindowIcon(QIcon(WINDOW_ICON_PATH));
    this->setWindowTitle(WINDOW_TITLE_TEXT);

    this->menuBar = new MenuBar(this);
    this->levelScene = new ChooseLevelScene(this->width(), MAIN_SCENE_WINDOW_H - this->menuBar->height(), this);
    this->levelScene->move(0, this->menuBar->height());
    this->levelScene->hide();

    this->mainScene = new MainScene(this->width(), MAIN_SCENE_WINDOW_H - this->menuBar->height(), this);
    this->mainScene->move(0, this->menuBar->height());
    this->mainScene->hide();

    connect(this->mainScene, &MainScene::RepSceneSignal, this, &MainWindow::RepSceneFucn);
    connect(this->levelScene, &ChooseLevelScene::RepSceneSignal, this, &MainWindow::RepSceneFucn);

    emit this->mainScene->RepSceneSignal(MAINSCENE);
}

MainWindow::~MainWindow()
{
    if(this->menuBar)
    {
        delete this->menuBar;
        this->menuBar = nullptr;
    }
    if(this->levelScene)
    {
        delete this->levelScene;
        this->levelScene = nullptr;
    }
    if(this->mainScene)
    {
        delete this->mainScene;
        this->mainScene = nullptr;
    }
    if(this->playScene)
    {
        delete this->playScene;
        this->playScene=nullptr;
    }
}

void MainWindow::RepSceneFucn(int code)
{
    // 切换界面回调函数,只要进入了这个界面就就一定切换界面,判断释放动态场景3
    if(this->playScene)
    {
        delete this->playScene;
        this->playScene=nullptr;
    }

    if(code== MAINSCENE) // 场景1
    {
        this->setWindowIcon(QIcon(WINDOW_ICON_PATH));
        this->setWindowTitle(WINDOW_TITLE_TEXT);
        this->mainScene->show();
        return;
    } else if(code== CHOOSELEVELSCENE)
    {
        this->setWindowIcon(QIcon(":/Coin0001.png"));
        this->setWindowTitle("选择关卡");
        this->levelScene->show();
        return;
    }
    if(code>0 && code<21)
    {
        this->setWindowIcon(QIcon(":/Coin0001.png"));
        this->setWindowTitle(QString("第%1关").arg(code));
        this->playScene = new PlayScene(code, this);
        this->playScene->move(0, this->menuBar->height());
        this->playScene->show();
        connect(this->playScene, &PlayScene::RepSceneSignal, this, &MainWindow::RepSceneFucn);
    }
}
