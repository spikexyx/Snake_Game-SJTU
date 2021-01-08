#ifndef GAME_H
#define GAME_H

#include "mainwindow.h"
#include "gameboard.h"
#include "food.h"
#include "other.h"
#include "Snake.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

const int BLOCKSIZE = 40;
const int ROW = 20;
const int COL = 20;

enum State{menu,play,pause,edit,over};

class SnakeGame : public QMainWindow
{
    Q_OBJECT
    friend class MainWindow;
    friend class Foods;
    friend class Snake;
    friend class AISnake;
    friend class wall;
    friend class ToolWidget;
    friend class StartWidget;
public:
    int snakenum;
    QList<Snake> snakes;
    Foods foods;
    Walls wall;
    State state;
    Point cursor;
    MainWindow *mainwindow;
    GameBoard *gameboard;
    Info *infowindow;
    QTimer *timer1,*timer2;

public:
    SnakeGame(QWidget *parent = 0);
    ~SnakeGame();
    void display();            //构造时显示主菜单
    void init();               //游戏面板初始化
    void changeState(State s); //改变状态
    void gameUpdate();         //更新状态
    void update1();            //第一条蛇update
    void update2();            //第二条蛇update
    void clearInfo();           //清除蛇和食物，解除timer信号
    void restart();             //重新开始
    void save();                //存档
    void resume();              //读档
    bool isEmpty(Point pt);    //用以判断地图某点是否有东西
    void Back();                //回到主菜单
    void keyPressEvent(QKeyEvent *event);//处理键盘事件
    void onePlay();             //单人模式
    void twoPlay();             //双人模式
    void Edit();                //编辑模式
public slots:
    void oneplayerSlot();
    void twoplayerSlot();
    void editSlot();
    void resumeSlot();
};

#endif // GAME_H
