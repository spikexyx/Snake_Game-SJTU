#ifndef MYSNAKE_H
#define MYSNAKE_H

#include "other.h"
#include "food.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QObject>
#include <QQueue>

enum direction{UP,DOWN,RIGHT,LEFT};

class Snake : public QList<Point>
{
    friend class SnakeGame;
private:
    int life;                      //当前生命值
    int length;                    //当前长度(分数)
    int curdir;                    //当前行进方向
    int speed;                     //当前速度
    int curInter;                  //当前时间间隔
    class SnakeGame *game;

public:
    Snake(SnakeGame *g);
    Snake(const Snake &obj);
    void move();                    //移动
    void turnDir(int d);            //转向
    void die();                     //生命值减一
    bool isDead();                  //判断是否已死亡
    void eat(int tp);               //进食
    void speedUp();                 //加速
    void speedDown();               //减速
    void pause();                   //暂停或继续
    void update();                  //更新
    virtual void updateinfo();      //更新info面板
};

#endif // MYSNAKE_H
