#include "snake.h"
#include "Game.h"

Snake::Snake(SnakeGame *g):game(g)
{
    curdir = RIGHT;
    life = 1;
    length = 0;
    speed = 1;
    curInter = 500;
}

Snake::Snake(const Snake &obj):game(obj.game)
{
    curdir=obj.curdir;
    life=obj.life;
    speed=obj.speed;
    length=obj.length;
    curInter = obj.curInter;
}

void Snake::move()
{
    switch (curdir) {
    case UP:
        if(this->front().y() > 0)
            push_front(Point(this->front().x(),this->front().y()-1));
        else push_front(Point(this->front().x(),ROW));
        break;
    case DOWN:
        if(this->front().y() < ROW)
            push_front(Point(this->front().x(),this->front().y()+1));
        else push_front(Point(this->front().x(),0));
        break;
    case RIGHT:
        if(this->front().x() < COL)
            push_front(Point(this->front().x()+1,this->front().y()));
        else push_front(Point(0,this->front().y()));
        break;
    case LEFT:
        if(this->front().x() > 0)
            push_front(Point(this->front().x()-1,this->front().y()));
        else push_front(Point(COL,this->front().y()));
        break;
    }
}

void Snake::update()
{
    move();
    int i = game->foods.contains(this->front());
    if(i>=0)
    {
        eat(game->foods.at(i).retType());
        game->foods.reProduce(i);
    }
    else this->pop_back();

    if(game->wall.contains(this->front()))                //判断是否撞到墙
        die();

    for (int i=1; i<size(); ++i)                      //判断是否撞到自己
    {
        if(this->at(i)==this->front())
            die();
    }

    for (int i=0; i<game->snakes.size(); ++i)         //判断有没有撞到其他蛇
    {
        if(game->snakes.indexOf(*this) == i)
            continue;
        if(game->snakes[i].contains(this->front()))
            die();
    }
    updateinfo();                                   //更新面板信息
}

void Snake::turnDir(int d)
{
    if(d == -1) return;
    switch (d)
    {
        case UP:
            if(curdir!=DOWN)
                curdir=UP;
            break;
        case DOWN:
            if(curdir!=UP)
                curdir=DOWN;
            break;
        case LEFT:
            if(curdir!=RIGHT)
                curdir=LEFT;
            break;
        case RIGHT:
            if(curdir!=LEFT)
                curdir=RIGHT;
            break;
    }
}

void Snake::eat(int tp)
{
    length++;
    switch (tp) {
    case normal:
        break;
    case lifeplus:
        life+=1;
        break;
    case speedup:
        speedUp();
        break;
    case speeddown:
        speedDown();
        break;
    case decline:
        pop_back();
        pop_back();
        length--;
        length--;
       break;
    }
}

void Snake::speedUp()
{
    speed++;
    curInter = curInter/1.6;
    if(game->snakes.indexOf(*this)==0)
        game->timer1->setInterval(curInter);
    else game->timer2->setInterval(curInter);
}

void Snake::speedDown()
{
    speed--;
    curInter = curInter*1.6;
    if(game->snakes.indexOf(*this)==0)
        game->timer1->setInterval(curInter);
    else game->timer2->setInterval(curInter);
}

void Snake::die()
{
    life--;
    if(isDead())
        game->changeState(over);
}

bool Snake::isDead()
{
    return life < 1;
}

void Snake::updateinfo()
{
    int i = game->snakes.indexOf(*this);   //用以判断是哪一条蛇
    if (i==0)
        game->infowindow->score1->setText("Snake1's score: "+QString::number(length)+"\n life: "+QString::number(life));
    else game->infowindow->score2->setText("Snake2's score: "+QString::number(length)+"\n life: "+QString::number(life));
}
