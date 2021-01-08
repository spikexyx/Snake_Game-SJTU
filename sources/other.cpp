#include "other.h"
#include "Game.h"

Info::Info(SnakeGame *g, QWidget *parent):QWidget(parent)
{
    this->setGeometry(840,0,360,840);
    game = g;

    //第一条蛇的分数栏
    score1 = new QLabel(this);
    score1->setGeometry(20,40,320,100);
    score1->setText("Snake1's score: 0 \n life: 1");

    //第二条蛇的分数栏
    score2 = new QLabel(this);
    score2->setGeometry(20,140,320,100);
    score2->setText("Snake2's score: 0 \n life: 1");

    //提示信息栏
    tip = new QLabel(this);
    tip->setGeometry(20,240,320,300);
    tip->setText("按下P键暂停\n"
                 "暂停状态下按E键进入编辑模式\n"
                 "编辑模式下，L放墙，FGHJK放食物\n\n"
                 "不同食物：\n"
                 "\t黄色(F)：普通食物\n"
                 "\t青色(G)：加速\n"
                 "\t紫色(H)：减速\n"
                 "\t红色(J)：生命值加1\n"
                 "\t橙色(K)：长度减1");

    restart = new QPushButton("restart",this);
    back = new QPushButton("back",this);
    back->setGeometry(80,700,200,80);
    restart->setGeometry(80,600,200,80);
    connect(restart,&QPushButton::clicked,game,&SnakeGame::restart);
    connect(back,&QPushButton::clicked,game,&SnakeGame::Back);
}
