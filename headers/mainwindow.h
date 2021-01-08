#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QTimer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    QPushButton *oneplbtn;
    QPushButton *twoplbtn;
    QPushButton *exitbtn;
    QPushButton *editbtn;
    QPushButton *resumebtn;
    QPushButton *aibtn;

    QTimer *timer;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
public slots:
    void exitSlot();
};
#endif // MAINWINDOW_H
