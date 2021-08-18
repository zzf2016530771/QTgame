#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
//#include "chooselevelscene.h"
//可能是和playscene.h相互嵌套了，chooselevelscene.h中的PlayScene *pScene = NULL;出错，注释掉后通过
#include <QMenuBar>
#include <QPainter>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelnum);
    void paintEvent(QPaintEvent  *);
    int levelIndex;//内部成员属性  记录所选关卡
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
