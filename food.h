#ifndef FOOD_H
#define FOOD_H

#include "other.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>

enum foodType{normal,lifeplus,speedup,speeddown,decline};//食物类型
//食物的封装类
class Food: public Point
{
public:
    int type;

public:
    Food(int x=0, int y=0, foodType tp=normal):Point(x,y),type(tp){}
    int retType() const {return type;}
};

//游戏中食物的类
class Foods: public QList<Food>
{
    friend class Food;
    friend class SnakeGame;
private:
    class SnakeGame *game;
    int cnt;   //用以计数目前已经产生的食物数目

public:
    Foods(SnakeGame *g):game(g){cnt = 0;}
    void Produce();             //用以产生食物
    void reProduce(int i);      //用以某食物被吃后重新产生食物
    int contains(Point pt);        //判断食物是否含有以及位置
    bool isLegal(const Point &pt);    //判断是否是合法的产生位置
    void addFood(foodType tp);      //添加指定类型的食物
};

#endif // FOOD_H
