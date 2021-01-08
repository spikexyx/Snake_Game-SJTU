#include "mainwindow.h"
#include "Game.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1200,840);

    QLabel *label = new QLabel(this);
    label=new QLabel(this);
    label->setStyleSheet("color:white; font:bold 75 60pt");
    label->setText("Snake Game");
    label->setGeometry(320,50,600,200);

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                    QBrush(QPixmap("./back1.jpg").scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
    this->setPalette(palette);
    //设置各个按钮与信号
    //单人游戏模式
    oneplbtn = new QPushButton("1 Player",this);
    oneplbtn->setGeometry(500,280,200,80);
    connect(oneplbtn,SIGNAL(clicked()),static_cast<SnakeGame*>(parent),SLOT(oneplayerSlot()));
    oneplbtn->setFocusPolicy(Qt::NoFocus);

    //双人游戏模式
    twoplbtn = new QPushButton("2 Players",this);
    twoplbtn->setGeometry(500,380,200,80);
    connect(twoplbtn,SIGNAL(clicked()),static_cast<SnakeGame*>(parent),SLOT(twoplayerSlot()));
    twoplbtn->setFocusPolicy(Qt::NoFocus);

    //编辑地图
    editbtn = new QPushButton("Edit",this);
    editbtn->setGeometry(500,480,200,80);
    connect(editbtn,SIGNAL(clicked()),static_cast<SnakeGame*>(parent),SLOT(editSlot()));
    editbtn->setFocusPolicy(Qt::NoFocus);

    //存档
    resumebtn = new QPushButton("Resume",this);
    resumebtn->setGeometry(500,580,200,80);
    connect(resumebtn,SIGNAL(clicked()),static_cast<SnakeGame*>(parent),SLOT(resumeSlot()));
    resumebtn->setFocusPolicy(Qt::NoFocus);

    //退出
    exitbtn = new QPushButton("Exit",this);
    exitbtn->setGeometry(500,680,200,80);
    connect(exitbtn,SIGNAL(clicked()),this,SLOT(exitSlot()));
    exitbtn->setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow()
{
    delete oneplbtn;
    delete twoplbtn;
    delete exitbtn;
    delete editbtn;
    delete resumebtn;
    delete aibtn;
}

void MainWindow::exitSlot()
{
    exit(0);
}
