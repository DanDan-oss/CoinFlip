#include "scene.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QPropertyAnimation>

int gameCoinArray[20][4][4] = {
    { {1, 1, 1, 1}, {1, 1, 0, 1}, {1, 0, 0, 0}, {1, 1, 0, 1} }, //1
    { {1, 0, 1, 1}, {0, 0, 1, 1}, {1, 1, 0, 0}, {1, 1, 0, 1} }, //2
    { {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} }, //3
    { {0, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 1, 1}, {1, 1, 1, 1} }, //4
    { {1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 1} }, //5
    { {1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 0, 1} }, //6
    { {0, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0} }, //7
    { {0, 1, 0, 1}, {1, 0, 0, 0}, {0, 0, 0, 1}, {1, 0, 1, 0} }, //8
    { {1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 1} }, //9
    { {1, 0, 1, 1}, {1, 1, 0, 0}, {0, 0, 1, 1}, {1, 1, 0, 1} }, //10
    { {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0} }, //11
    { {0, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0} }, //12
    { {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0} }, //13
    { {1, 0, 1, 1}, {0, 1, 0, 1}, {1, 0, 1, 0}, {1, 1, 0, 1} }, //14
    { {0, 1, 0, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 1} }, //15
    { {0, 1, 1, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 0} }, //16
    { {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0} }, //17
    { {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0} }, //18
    { {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0} }, //19
    { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} } //20
};


MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    this->initScene(MAIN_SCENE_WINDOW_W, MAIN_SCENE_WINDOW_H-MAIN_MENUBAR_H);
}
MainScene::MainScene(int iSceneWidget, int iSceneHeight, QWidget *parent) :QWidget(parent)
{
    this->initScene(iSceneWidget, iSceneHeight);
}

MainScene::~MainScene()
{
    if(this->startButton)
    {
        delete this->startButton;
        this->startButton = nullptr;
    }

}

void MainScene::initScene(int iSceneWidget, int iSceneHeight)
{
    this->setFixedSize(iSceneWidget, iSceneHeight);

    // 开始按钮
    this->startButton = new CustomButton(":/MenuSceneStartButton.png", this);
   this->startButton->move((this->width()- this->startButton->width())*0.5, this->height()*0.7);

    connect(this->startButton, &QPushButton::clicked, [=]()   // 主界面开始按钮被点击后释放了
    {
        this->startButton->zoom(50, 300);
        QTimer::singleShot(300, [=]()
        {
            this->hide();
            emit this->RepSceneSignal(CHOOSELEVELSCENE);       // 发送切换界面信号,前往关卡选择界面

        });
    });

}

void MainScene::paintEvent(QPaintEvent* event)
{
    // 初始化主场景背景图
    QPainter painter(this);
    QPixmap pixMap;
    int iHeight= this->height(), iWidget=this->width();

    pixMap.load(":/PlayLevelSceneBg.png");
    //pixMap.load(":/20220406022318.jpg");
    painter.drawPixmap(0, 0, iWidget,iHeight, pixMap);

    pixMap.load(":/Title.png");
    pixMap = pixMap.scaled(pixMap.width()*0.5, pixMap.height()*0.5);
    painter.drawPixmap(10, 30, pixMap.width(), pixMap.height(), pixMap);
    return QWidget::paintEvent(event);
}



//=============================================================
ChooseLevelScene::ChooseLevelScene(int iSceneWidget, int iSceneHeight, QWidget *parent) :QWidget(parent)
{
    this->initScene(iSceneWidget, iSceneHeight);
    return;
}


ChooseLevelScene::~ChooseLevelScene()
{
    if(this->backButton)
    {
        delete this->backButton;
        this->backButton = nullptr;
    }
}

void ChooseLevelScene::initScene(int iSceneWidget, int iSceneHeight)
{
    CustomButton* playButton = nullptr;
    QLabel* label = nullptr;

    this->setFixedSize(iSceneWidget, iSceneHeight); // 设置关卡场景大小
    this->backButton = new CustomButton(":/BackButton.png", ":/BackButtonSelected.png", this);
    this->backButton->move(this->width()-this->backButton->width(), this->height()-this->backButton->height());

    connect(this->backButton, &QPushButton::clicked, [=](){
        this->hide();
        emit this->RepSceneSignal(MAINSCENE);
    });

    for(int i=0; i<20; i++)
    {
        playButton = new CustomButton(":/LevelIcon.png", this);
        playButton->move(25+(i%4)*70, 130+(i/4)*70);
        label = new QLabel( QString::number(i+1), playButton);
        label->setFixedSize(playButton->width(), playButton->height());
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        label->setAlignment(Qt::AlignCenter);
        connect(playButton, &QPushButton::clicked, [=](){
            this->RepSceneSignal(i+1);
            this->hide();
        });
    }
    return;
}

void ChooseLevelScene::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pixMap;
    int iHeight= this->height(), iWidget=this->width();

    pixMap.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, iWidget, iHeight, pixMap);

    pixMap.load(":/Title.png");
    painter.drawPixmap((this->width()-pixMap.width())*0.5, 30,
                       pixMap.width(), pixMap.height(), pixMap);
    return QWidget::paintEvent(event);
}


//===================================================================
PlayScene::PlayScene(int Index, QWidget *parent, int iSceneWidget, int iSceneHeight)
    : levelIndex(Index), QWidget(parent)
{
    this->initScene(Index, iSceneWidget, iSceneHeight);
    return;
}

PlayScene::PlayScene(int Index, int iSceneWidget, int iSceneHeight, QWidget *parent)
    : levelIndex(Index), QWidget(parent)
{
    this->initScene(Index, iSceneWidget, iSceneHeight);
    return;
}

 PlayScene::~PlayScene()
 {
    if(this->backButton)
    {
        delete this->backButton;
        this->backButton = nullptr;
    }
    if(this->label)
    {
        delete this->label;
        this->label = nullptr;
    }
    if(this->imageSuccess)
    {
        delete this->imageSuccess;
        this->imageSuccess = nullptr;
    }

 }

void PlayScene::initScene(int Index, int iSceneWidget, int iSceneHeight)
{
    QPixmap pixMap;
    int pixWidth=0, pixHeight=0;

    this->setFixedSize(iSceneWidget, iSceneHeight);
    this->backButton = new CustomButton(":/BackButton.png", ":/BackButtonSelected.png", this);
    this->backButton->move(this->width()-this->backButton->width(), this->height()-this->backButton->height());

    connect(this->backButton, &QPushButton::clicked, [=](){
        emit this->RepSceneSignal(CHOOSELEVELSCENE);
    });
    this->label = new QLabel(QString("Level %1").arg(Index), this);
    this->label->setFont(QFont("华文行楷", 30));
    this->label->setGeometry(QRect(30, this->height() - 50,120, 50));
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            this->coinArray[i][j] = new Coins(i, j, gameCoinArray[Index-1][i][j], this);
            this->coinArray[i][j]->move(59 + i*50,204+j*50);

            connect(this->coinArray[i][j], &Coins::FlipCoinSignal, this, &PlayScene::RepFlipCoin);
        }

    this->imageSuccess = new QLabel(this);
    if(!pixMap.load(":/LevelCompletedDialogBg.png"))
        return;
   pixHeight =pixMap.height();
   pixWidth= pixMap.width();
   this->imageSuccess->setPixmap(pixMap);
   this->imageSuccess->setFixedSize(pixWidth, pixHeight);
   this->imageSuccess->move((this->width() - pixWidth)/2, -pixHeight);
    return;
}

void PlayScene::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pixMap;
    int iHeight= this->height(), iWidget=this->width();

    pixMap.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, iWidget, iHeight, pixMap);

    pixMap.load(":/Title.png");
    painter.drawPixmap((this->width()-pixMap.width())*0.5, 30,
                       pixMap.width(), pixMap.height(), pixMap);
}

bool PlayScene::isGameSuccess()
{
    bool isSuccess = true;

    for(int i=0; i<4; ++i)
        for(int j=0; j<4;++j)
        {
            if(!(this->coinArray[i][j]->getStance()))
            {
                isSuccess= false;
                break;
            }
        }
    if(isSuccess)
        return true;
    return false;
}

void PlayScene::setAllCoinDisable(bool isTrue)
{
    for(int i=0; i<4; ++i)
        for(int j=0; j<4;++j)
            if(this->coinArray[i][j])
                this->coinArray[i][j]->setDisable(isTrue);

    return;
}



void PlayScene::RepFlipCoin(int posX, int posY)
{
    this->setAllCoinDisable(true);
    if(posY>0)     //判断上
        this->coinArray[posX][posY-1]->flipCoin();
    if(posY<3)  //判断下
        this->coinArray[posX][posY+1]->flipCoin();
    if(posX>0)   //判断左边
        this->coinArray[posX-1][posY]->flipCoin();
    if(posX<3)  //判断右边
        this->coinArray[posX+1][posY]->flipCoin();

    if(this->isGameSuccess())
    {
        qDebug()<<"游戏胜利";
        this->gameSuccess();

        return;
    }
    this->setAllCoinDisable(false);
}

 void PlayScene::gameSuccess()
 {
    QPropertyAnimation* animation = new QPropertyAnimation(this->imageSuccess, "geometry", this);
    int curX = this->imageSuccess->x(), curY=this->imageSuccess->y();
    int iWidth = this->imageSuccess->width(), iHeight = this->imageSuccess->height();

    if(!this->imageSuccess)
        return;
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setStartValue(QRect(curX, curY, iWidth, iHeight));
    animation->setEndValue(QRect(curX, ( this->height() -iHeight)/4 , iWidth, iHeight));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
 }
