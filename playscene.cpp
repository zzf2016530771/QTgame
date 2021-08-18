#include "playscene.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}


PlayScene::PlayScene(int levelnum)
{
    //qDebug() << "当前关卡为"<< index;
    this->levelIndex = levelnum;
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

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
    MyPushButton * backbutton = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbutton->setParent(this);
    backbutton->move(this->width()-backbutton->width(),this->height()-backbutton->height());

    //返回按钮功能实现
    connect(backbutton,&MyPushButton::clicked,[=](){
       QTimer::singleShot(500, this,[=](){
           this->hide();
           //触发自定义信号，关闭自身，该信号写到 signals下做声明
           emit this->chooseSceneBack();
            }
       );
    });

    //当前关卡标题
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30, this->height() - 50,120, 50)); //设置大小和位置


    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
           //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //金币对象
            MyCoin * coin = new MyCoin(":/res/Coin0001.png");
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);

        }
    }


}

void PlayScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}
