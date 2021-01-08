#ifndef OTHER_H
#define OTHER_H

#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QObject>

class Point : public QPoint
{
public:
    Point(){}
    Point(int x,int y):QPoint(x,y){}

    bool operator==(const Point &t) const {
        return (x() == t.x()) && (y() == t.y());
    }
    bool operator!=(const Point &t) const {
        return (x() != t.x()) || (y() != t.y());
    }
    bool operator<(const Point &t) const {
        return x() == t.x() ? y() < t.y() : x() < t.x();
    }
};

class Info : public QWidget
{
    Q_OBJECT
    friend class SnakeGame;
    friend class Snake;
private:
    class SnakeGame *game;
    QPushButton *restart,*back;
    QLabel *score1,*score2,*tip;

public:
    Info(SnakeGame *g, QWidget *parent = nullptr);
};

class Walls : public QList<Point>
{
public:
    Walls(){}
};

#endif // OTHER_H
