#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);


    MyPushButton(QString normalImg,QString pressImg = "");
    //成员属性
    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径


    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
