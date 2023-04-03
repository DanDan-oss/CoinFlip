#include "custom.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QTimer>

char imagePth[][30] = {":/Coin0001.png", ":/Coin0002.png",  ":/Coin0003.png", ":/Coin0004.png", ":/Coin0005.png",
                  ":/Coin0006.png", ":/Coin0007.png", ":/Coin0008.png" };


MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{
    QMenu* menu= NULL;
    QAction* action = NULL;

    this->setFixedSize(MAIN_SCENE_WINDOW_W, 21);

    // 菜单栏 开始
    menu = this->addMenu("开始(S)");
    action = menu->addAction("重新开始");
    action = menu->addAction("开始选关");
    action = menu->addAction("退出");

    // 菜单栏 作弊
    menu = this->addMenu("作弊(C)");

    // 菜单栏 关于
    menu = this->addMenu( "帮助(A)");
    action = menu->addAction(QIcon(":/Coin0001.png"),"玩法介绍");
    action = menu->addAction(QIcon(":/liaoyang.jpg"),"关于开发者");
    return;
}

//========================================================
CustomButton::CustomButton(QWidget *parent) : QPushButton(parent)
{
     this->setButtonIconStyle("");
    return;
}
CustomButton::CustomButton(QString defImage, QWidget *parent): defaultImage(defImage), QPushButton(parent)
{
    this->setButtonIconStyle(defImage);
    return;
}

CustomButton::CustomButton(QString defImage, QString specImage, QWidget *parent): defaultImage(defImage), specialImage(specImage), QPushButton(parent)
{
    this->setButtonIconStyle(defImage);
    return;
}

void CustomButton::setButtonIconStyle(QString imagePath)
{
    QPixmap pix;
    int iWidth, iHeight;

    if(imagePath.isEmpty())
        return;
    if(!pix.load(imagePath))
        return;
    iWidth = pix.width();
    iHeight= pix.height();
    this->setFixedSize(iWidth, iHeight);      // 设置按钮的大小
    this->setStyleSheet("QPushButton{border:0px;}");    // 设置按钮不规则样式(边距为0)
    this->setIcon(pix);                                 // 设置按钮的背景图标
    this->setIconSize(QSize(iWidth, iHeight));   // 设置背景图标大小
    return;
}

void CustomButton::mousePressEvent(QMouseEvent *ev)
{
    if(!this->specialImage.isEmpty())        // 判断鼠标按下动画是否有值
        this->setButtonIconStyle(this->specialImage);
    return QPushButton::mousePressEvent(ev);
}

void CustomButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if(!this->specialImage.isEmpty())
        this->setButtonIconStyle(defaultImage);
    return QPushButton::mouseReleaseEvent(ev);
}

// 按钮跳跃动画
void CustomButton::zoom(int distance, int mesc)
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry", this);     // 创建几何图形动画类
    int iX=this->x(), iY=this->y(), iHeight=this->height(), iWidth=this->width();       // 获取当前按钮控件的坐标和宽高

    animation->setDuration(mesc);        // 如果动画时间未完成,获取的多次触发 x和x坐标不准
    animation->setEasingCurve(QEasingCurve::OutBounce);     // 设置缓和曲线 弹跳效果

    // 按下向下弹
    animation->setStartValue(QRect(iX, iY, iHeight, iWidth));   // 设置动画起始位置(x, y ,width, height)
    animation->setEndValue(QRect(iX, iY+distance, iHeight, iWidth));  // 设置动画结束位置(x, y ,width, height)
    animation->start();                                         // 执行动画
    // 回弹
    animation->setStartValue(QRect(iX, iY+distance, iHeight, iWidth));   // 设置回弹动画起始位置(x, y ,width, height)
    animation->setEndValue(QRect(iX, iY, iHeight, iWidth));         // 设置回弹动画结束位置(x, y ,width, height)
    animation->start(QAbstractAnimation::DeleteWhenStopped);      // 动画执行完后删除对象
    return;
}

void CustomButton::zoomUp(int distance, int mesc)
{
    // CustomButton::与zoom()执行流程相同, 查看注释
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    int iX=this->x(), iY=this->y(), iHeight=this->height(), iWidth=this->width();

    animation->setDuration(mesc);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setStartValue(QRect(iX, iY, iHeight, iWidth));
    animation->setEndValue(QRect(iX, iY+distance, iHeight, iWidth));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CustomButton::zoomDown(int distance, int mesc)
{
    // CustomButton::与zoom()执行流程相同, 查看注释
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    int iX=this->x(), iY=this->y(), iHeight=this->height(), iWidth=this->width();

    animation->setDuration(mesc);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setStartValue(QRect(iX, iY+distance, iHeight, iWidth));
    animation->setEndValue(QRect(iX, iY, iHeight, iWidth));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


//============================================
Coins::Coins(int posX, int posY, bool showStance, QString strbackgroundImage, QString strGoldiamge,
                QString strSilImage, QWidget *parent) : curX(posX), curY(posY), stance(showStance),
    backgrpundImage(strbackgroundImage),goldImage(strGoldiamge), silverImage(strSilImage), QWidget(parent)
{
    this->initCoins(showStance, strbackgroundImage, strGoldiamge, strSilImage);
    return;
}

Coins::Coins(int posX, int posY, bool showStance, QWidget *parent, QString strbackgroundImage, QString strGoldiamge,
       QString strSilImage): curX(posX), curY(posY), stance(showStance),QWidget(parent),backgrpundImage(strbackgroundImage),
        goldImage(strGoldiamge),silverImage(strSilImage)
{
    this->initCoins(showStance, strbackgroundImage, strGoldiamge, strSilImage);
    return;
}

void Coins::initCoins(bool showStance, QString strbackgroundImage, QString strGoldiamge, QString strSilImage)
{
    QPixmap pixMap;
    int iWidth=0, iHeight=0;

    if(!pixMap.load(strbackgroundImage) )
        return;
    iWidth =pixMap.width();
    iHeight =pixMap.height();
    this->setFixedSize(iWidth, iHeight);
    this->label = new QLabel(this);
    this->label->setFixedSize(iWidth, iHeight );
    this->label->setPixmap(pixMap);
    this->label->setAttribute(Qt::WA_TransparentForMouseEvents);
    if(showStance)
    {
        if(!pixMap.load(strGoldiamge) )
            return;
    }else
    {
        if(!pixMap.load(strSilImage) )
            return;
    }

    iWidth =pixMap.width();
    iHeight =pixMap.height();
    this->coinsButton = new QPushButton(this);
    this->coinsButton->setFixedSize(iWidth, iHeight);
    this->coinsButton->setStyleSheet("QPushButton{border:0px;}");
    this->coinsButton->setIcon(pixMap);
    this->coinsButton->setIconSize(QSize(iWidth, iHeight));
    this->coinsButton->move((this->width()-iWidth)/2, (this->height()-iHeight)/2);
    this->coinsButton->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->time = new QTimer(this);

    connect(this->time, &QTimer::timeout, [=](){
        if(this->curImageNum>7 || this->curImageNum<0)
        {
            this->time->stop();
            this->isAnimation = 0;
            return;
        }
        this->showAnimation(imagePth[curImageNum]);
        if(this->stance)
            this->curImageNum--;
        else
            this->curImageNum++;
    });
    return;
}

bool Coins::getStance()
{
    return this->stance;
}

void Coins::setDisable(bool disable)
{
    this->isDisable =disable;
    return;
}

void Coins::showAnimation(const char* chageImagePath)
{
    QPixmap pixMap;
    int iWidth=0, iHeight=0;

    if(!pixMap.load(chageImagePath))
        return;
    iWidth =pixMap.width();
    iHeight =pixMap.height();
    this->coinsButton->setFixedSize(iWidth, iHeight);
    this->coinsButton->setStyleSheet("QPushButton{border:0px;}");
    this->coinsButton->setIcon(pixMap);
    this->coinsButton->setIconSize(QSize(iWidth, iHeight));
    this->coinsButton->move((this->width()-iWidth)/2, (this->height()-iHeight)/2);
    return;
}

void Coins::flipCoin()
{
    this->isAnimation= true;
    this->stance = !this->stance;
    if(this->stance)
        this->curImageNum = 7;
    else
        this->curImageNum = 0;
    this->time->start(30);
}

void Coins::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->isAnimation || this->isDisable)
        return;
    this->flipCoin();
    emit this->FlipCoinSignal(this->curX, this->curY);
}



