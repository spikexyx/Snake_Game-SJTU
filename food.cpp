#include "food.h"
#include "Game.h"

bool Foods::isLegal(const Point &pt)
{
    if(game->wall.contains(pt))    return false;  //此处有墙则不合法
    if(game->foods.contains(pt)>=0) return false;  //此处已有食物则不合法
    for (int i=0; i<game->snakes.size(); ++i)   //不能在蛇身体里
    {
        if(game->snakes[i].contains(pt))
            return false;
    }
    return true;
}

void Foods::addFood(foodType tp)
{
    Food fd((rand()%COL),(rand()%ROW),tp);
    //找到可以放食物的地方
    while (!isLegal(Point(fd)))
    {
        fd.setX(rand()%COL);
        fd.setY(rand()%ROW);
    }

    this->push_back(fd);
    cnt++;
}

void Foods::Produce()
{
    addFood(normal);
    //在特定数目后产生特殊食物
    if(cnt%7==0&&cnt!=0) addFood(decline);
    else if(cnt%3==0&cnt!=0) addFood(speedup);
    else if(cnt%5==0&&cnt!=0) addFood(speeddown);
    else if(cnt%11==0&&cnt!=0) addFood(lifeplus);
}

//返回此点含有的食物下标，没有食物就返回-1
int Foods::contains(Point pt)
{
    for (int i=0;i<this->size();i++)
    {
        if(Point(this->at(i))==pt)
            return i;
    }
    return -1;
}

void Foods::reProduce(int i)
{
    this->removeAt(i);
    Produce();
}
