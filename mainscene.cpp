#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(320,588);
    //设置应用图片
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    setWindowTitle("老凡翻金币");
    //退出
    connect(ui->actionQuit,&QAction::triggered,[=](){this->close();});

    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);

    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//具有缩放功能


    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}
