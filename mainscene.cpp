#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include "chooselevelscene.h"


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


    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);

    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);



    //监听返回对象
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        chooseScene->hide();//将选择关卡隐藏
        this->show();//显示主界面
    });

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;
    //监听返回对象
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene->hide();//将选择关卡隐藏
        this->show();//显示主界面
    });


    //监听点击事件，执行特效
    connect(startBtn,&MyPushButton::clicked,[=](){
        startBtn->zoom1(); //向下跳跃
        startBtn->zoom2(); //向上跳跃

        //延时0.5秒后 进入选择场景
        QTimer::singleShot(500, this,[=](){
            this->hide();//点击开始后自动隐藏开始菜单
            chooseScene->setGeometry(this->geometry());//使三个窗口切换时也在同一个位置
            chooseScene->show();//显示选择关卡的场景

            connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
               this->setGeometry(chooseScene->geometry());
                this->show();
            });
        });

    });

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
