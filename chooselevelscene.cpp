#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QtDebug>
#include "playscene.h"
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});
    //返回按钮
    MyPushButton *backbutton= new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbutton->setParent(this);
    backbutton->move(this->width()-backbutton->width(),this->height()-backbutton->height());

    //点击返回
    connect(backbutton,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了返回";
        //告诉主场景 我返回了  主场景监听返回按钮的信号
        QTimer::singleShot(500, this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            this->chooseSceneBack();//emit 自定义槽函数
            }
        );
    });

    //选择关卡按钮
    for(int i = 0 ; i < 20 ; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i%4)*70 , 130+ (i/4)*70);

        //监听选择关卡按钮的信号槽
        connect(menuBtn,&MyPushButton::clicked,[=](){
           // qDebug() << "select: " << i;
            if(pScene == NULL)  //游戏场景最好不用复用，直接移除掉创建新的场景
            {
                this->hide();
                pScene = new PlayScene(i+1); //将选择的关卡号 传入给PlayerScene
                pScene->setGeometry(this->geometry());
                pScene->show();

                connect(pScene,&PlayScene::chooseSceneBack,[=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = NULL;
                });


            }
        });



        //按钮上显示的文字
        QLabel * label = new QLabel;//可显示文字、gif图等
        label->setParent(menuBtn);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
        //label->move(25 + (i%4)*70 , 130+ (i/4)*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);  //鼠标事件穿透  label会挡住图片按钮
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.2,30,pix.width(),pix.height(),pix);

}
