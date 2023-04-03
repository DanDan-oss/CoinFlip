#ifndef CUSTOM_H
#define CUSTOM_H
#include <QMenuBar>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "macro.h"


// 自定义菜单栏
class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget *parent = nullptr);

signals:

};


// 自定义按钮类(不规则按钮)
class CustomButton : public QPushButton
{
    Q_OBJECT
public:

    explicit CustomButton(QWidget *parent = nullptr);
    CustomButton(QString defImage, QWidget *parent = nullptr);
    // 自定义按钮(默认显示图片,)-->显示凹凸效果
    CustomButton(QString defImage, QString specImage, QWidget *parent = nullptr);
    void setButtonIconStyle(QString imagePath);   // 设置按钮样式
    void zoom(int distance, int mesc);             // 使用用动画特弹跳(弹跳距离,动画时间)
    void zoomUp(int distance, int mesc);          // 使用动画特效向上跳跃(弹跳距离,动画时间)
    void zoomDown(int distance, int mesc);        // 使用动画特效向下跳跃(弹跳距离,动画时间)
signals:

private:
    QString defaultImage="";       // 默认图片
    QString specialImage="";       // 点击按下时显示的特效图片
    virtual void mousePressEvent(QMouseEvent *ev);      // 鼠标按下
    virtual void mouseReleaseEvent(QMouseEvent *ev);    // 鼠标弹起

};

class Coins : public QWidget
{
    Q_OBJECT
public:
    Coins(int posX, int posY, bool showStance = 0, QString strbackgroundImage = COINSIMAGE_BACKGROUND, QString strGoldiamge = COINSIMAGE_GOLD,
           QString strSilImage = COINSIMAGE_SILVER, QWidget *parent = nullptr);
    Coins(int posX, int posY, bool showStance = 0, QWidget *parent = nullptr, QString strbackgroundImage = COINSIMAGE_BACKGROUND, QString strGoldiamge = COINSIMAGE_GOLD,
           QString strSilImage = COINSIMAGE_SILVER);

    void initCoins(bool showStance, QString strbackgroundImage, QString strGoldiamge, QString strSilImage);
    void showAnimation(const char* chageImagePath);
    void flipCoin();
    virtual void mouseReleaseEvent(QMouseEvent *event);
    bool getStance();
    void setDisable(bool disable);

private:
    bool stance=0;          //0表示显示银币 1表示显示金币
    bool isAnimation = 0;   // 是否正在做动画
    bool isDisable = false;     // 是否禁用功能翻转,游戏胜利后禁用
    int curImageNum = 0;     //做动画时,当前做到第几张图片
    QString backgrpundImage= "";  // 背景图片
    QString goldImage="";       // 金币图
    QString silverImage="";       // 银币图

    QLabel* label = nullptr;
    QPushButton *coinsButton = nullptr;
    QTimer* time = nullptr;     // 响应定时器
    int curX=0;
    int curY=0;

signals:
    void FlipCoinSignal(int posX, int posY);
};

#endif // CUSTOM_H
