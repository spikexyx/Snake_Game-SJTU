#include "gameboard.h"
#include "Game.h"

GameBoard::GameBoard(SnakeGame *g, QWidget *parent) : QWidget(parent)
{
    game=g;
    resize(840,840);
    timer=new QTimer;
    timer->start(100);
    connect(timer,&QTimer::timeout,this,static_cast<void (QWidget::*)()>(&QWidget::update));
}

void GameBoard::paintWall(QPainter *p)
{
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(Qt::SolidPattern);
    for (int i=0;i<game->wall.size();++i) {
        p->drawRect(game->wall[i].x()*BLOCKSIZE,game->wall[i].y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
    }
    p->restore();
}

void GameBoard::paintCur(QPainter *p)
{
    p->save();
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);
    p->setPen(pen);
    p->drawRect(game->cursor.x()*BLOCKSIZE,game->cursor.y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
    p->restore();
}

void GameBoard::paintSnake(QPainter *p)
{
    p->save();
    p->setPen(Qt::NoPen);

    if(game->snakes.size() >= 1)  //单人游戏，只有一条蛇的情况
    {
        p->setBrush(Qt::darkGreen);
        p->drawRect(game->snakes[0].front().x()*BLOCKSIZE,game->snakes[0].front().y()*BLOCKSIZE,BLOCKSIZE-2,BLOCKSIZE-2);
        p->setBrush(Qt::green);
        for (int i=1;i<game->snakes[0].size();++i) {
            p->drawRect(game->snakes[0][i].x()*BLOCKSIZE,game->snakes[0][i].y()*BLOCKSIZE,BLOCKSIZE-2,BLOCKSIZE-2);
        }
        if(game->snakenum > 1)  //双人游戏情况，画第二条蛇
        {
            p->setBrush(Qt::darkBlue);
            p->drawRect(game->snakes[1].front().x()*BLOCKSIZE,game->snakes[1].front().y()*BLOCKSIZE,BLOCKSIZE-2,BLOCKSIZE-2);
            p->setBrush(Qt::blue);
            for (int i=1;i<game->snakes[1].size();++i) {
                p->drawRect(game->snakes[1][i].x()*BLOCKSIZE,game->snakes[1][i].y()*BLOCKSIZE,BLOCKSIZE-2,BLOCKSIZE-2);
            }
        }
    }

    p->restore();
}

void GameBoard::paintFood(QPainter *p)
{
    p->save();
    p->setPen(Qt::NoPen);
    for (int i=0;i<game->foods.size();++i)
    {
        switch (game->foods[i].retType()){
        case normal:
            p->setBrush(Qt::yellow);
            p->drawEllipse(game->foods[i].x()*BLOCKSIZE,game->foods[i].y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
            break;
        case lifeplus:
            p->setBrush(Qt::darkRed);
            p->drawEllipse(game->foods[i].x()*BLOCKSIZE,game->foods[i].y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
            break;
        case speedup:
            p->setBrush(Qt::cyan);
            p->drawEllipse(game->foods[i].x()*BLOCKSIZE,game->foods[i].y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
            break;
        case speeddown:
            p->setBrush(Qt::darkMagenta);
            p->drawEllipse(game->foods[i].x()*BLOCKSIZE,game->foods[i].y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
            break;
        case decline:
            p->setBrush(QColor(255,165,0));
            p->drawEllipse(game->foods[i].x()*BLOCKSIZE,game->foods[i].y()*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE);
            break;
        }
    }
    p->restore();
}

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap("./3.jpg"));
    paintSnake(&p);
    paintFood(&p);
    paintWall(&p);
    paintCur(&p);
}
