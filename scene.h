#ifndef SCENE_H
#define SCENE_H
#include <QWidget>
#include <QLabel>
#include "macro.h"
#include "custom.h"

// 窗口主场景类===========================
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    MainScene(int iSceneWidget, int iSceneHeight, QWidget *parent = nullptr);
    ~MainScene();
    virtual void paintEvent(QPaintEvent* event);    // 绘制事件,绘制背景
    void initScene(int iSceneWidget, int iSceneHeight);     // 初始化主场景

protected:
    CustomButton* startButton = nullptr;
signals:
    void RepSceneSignal(int code);
};


// 选择关卡窗口类====================
class ChooseLevelScene : public QWidget
{
    Q_OBJECT
public:
    ChooseLevelScene(int iSceneWidget= MAIN_SCENE_WINDOW_W, int iSceneHeight = MAIN_SCENE_WINDOW_H-MAIN_MENUBAR_H, QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);    // 绘制事件,绘制背景
    void initScene(int iSceneWidget, int iSceneHeight); // 初始化关卡场景
    ~ChooseLevelScene();
private:
    CustomButton* backButton = nullptr;
signals:
    void RepSceneSignal(int code);
};


// 游玩场景======================
class PlayScene : public QWidget
{
    Q_OBJECT
public:
    PlayScene(int Index=1, QWidget *parent = nullptr, int iSceneWidget = MAIN_SCENE_WINDOW_W,
              int iSceneHeight= MAIN_SCENE_WINDOW_H-MAIN_MENUBAR_H);

    PlayScene(int Index=1, int iSceneWidget = MAIN_SCENE_WINDOW_W,
              int iSceneHeight= MAIN_SCENE_WINDOW_H-MAIN_MENUBAR_H, QWidget *parent = nullptr);

    ~PlayScene();
    void initScene(int Index, int iSceneWidget, int iSceneHeight);
    virtual void paintEvent(QPaintEvent* event);    // 绘制事件,绘制背景
    bool isGameSuccess();       // 判断游戏场景类是否全部都变成金币了
    void setAllCoinDisable(bool isTrue);    // 设置所有金币按钮禁用
    void gameSuccess();         // 游戏胜利,弹出下拉胜利框
signals:
    void RepSceneSignal(int code);
private:
    CustomButton* backButton = nullptr;
    QLabel* label = nullptr;
    QLabel* imageSuccess = nullptr;
    int levelIndex = 0;
    Coins* coinArray[4][4] = {0};


public slots:
    void RepFlipCoin(int posX, int posY);     // 当某个金币反转时,发送信号给场景,让场景类翻转附近金币
};
#endif // SCENE_H
