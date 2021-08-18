#include "mycoin.h"
#include <QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}


MyCoin::MyCoin(QString butImg)
{

    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(!ret)
    {
        qDebug() << butImg << "加载图片失败!";
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet("QPushButton{border:0px;}");//去除图片边框，使之只留金币部分
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}
