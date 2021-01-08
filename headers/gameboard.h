#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "food.h"
#include "Snake.h"
#include "mainwindow.h"
#include "other.h"
#include <QPoint>
#include <QKeyEvent>
#include <QWidget>
#include <QObject>

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    class SnakeGame *game;
    QTimer *timer;
    void init();
public:
    GameBoard(SnakeGame *g, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void paintSnake(QPainter *p);
    void paintFood(QPainter *p);
    void paintWall(QPainter *p);
    void paintCur(QPainter *p);
};

#endif // GAMEBOARD_H
