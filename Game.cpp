#include "Game.h"

SnakeGame::SnakeGame(QWidget *parent)
    : QMainWindow(parent),foods(this)
{
    setWindowTitle("SnakeGame");
    resize(1200, 840);//设置窗口大小

    srand(time(nullptr));
    mainwindow = new MainWindow(this);
    gameboard = new GameBoard(this,this);
    infowindow = new Info(this,this);
    setFocusPolicy(Qt::StrongFocus);

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    display();
}

SnakeGame::~SnakeGame()
{
    delete gameboard;
    delete mainwindow;
    delete infowindow;
    delete timer1;
    delete timer2;
}

void SnakeGame::display()
{
    state = menu;
    snakenum = 0;

    gameboard->close();
    mainwindow->show();
    infowindow->close();
}

void SnakeGame::init()
{
    clearInfo();
    for (int i=0;i<snakenum;++i)
    {
        snakes.push_back(Snake(this));
        snakes.back().push_front(Point(COL/2,ROW/2+2*i));
    }
    timer1->start(snakes[0].curInter);
    if(snakenum>1)
        timer2->start(snakes[1].curInter);
    foods.Produce();
}

//改变游戏状态控制函数
void SnakeGame::changeState(State s)
{
    switch (s){
    case menu:
        mainwindow->show();
        gameboard->close();
        infowindow->close();
        state=menu;
        break;
    case play:
        init();
        mainwindow->close();
        gameboard->show();
        infowindow->show();
        connect(timer1,&QTimer::timeout,this,&SnakeGame::update1);
        if(snakenum>1) connect(timer2,&QTimer::timeout,this,&SnakeGame::update2);
        state=play;
        break;
    case pause:
        if(state==play)
        {
            timer1->stop();
            timer2->stop();
            state=pause;
            break;
        }
        if(state==pause)
        {
            state=play;
            timer1->start(400/snakes[0].speed);
            if(snakenum>1) timer2->start(400/snakes[1].speed);
            break;
        }
        if(state==edit) state=pause;
        break;
    case over:
        state=over;
        timer1->stop();
        timer2->stop();
        //单人游戏判断游戏结束给出弹窗
        if(snakenum==1){
            QMessageBox *msgBox;
            msgBox = new QMessageBox("info",
                "!GAME OVER!",
                QMessageBox::Critical,
                QMessageBox::Ok | QMessageBox::Default,
                QMessageBox::Cancel | QMessageBox::Escape,
                0);
            msgBox->show();
        }
        //双人游戏判断游戏结束给出弹窗
        else if(snakenum==2){
            if(snakes[0].length>snakes[1].length){
                QMessageBox *msgBox;
                msgBox = new QMessageBox("info",
                    "Player1 WINS!",
                    QMessageBox::NoIcon,
                    QMessageBox::Ok | QMessageBox::Default,
                    QMessageBox::Cancel | QMessageBox::Escape,
                    0);
                msgBox->show();
            }
            else if(snakes[1].length>snakes[0].length){
                QMessageBox *msgBox;
                msgBox = new QMessageBox("info",
                    "Player2 WINS!",
                    QMessageBox::NoIcon,
                    QMessageBox::Ok | QMessageBox::Default,
                    QMessageBox::Cancel | QMessageBox::Escape,
                    0);
                msgBox->show();
            }
            else {
                QMessageBox *msgBox;
                msgBox = new QMessageBox("info",
                    "Ends in tie!",
                    QMessageBox::NoIcon,
                    QMessageBox::Ok | QMessageBox::Default,
                    QMessageBox::Cancel | QMessageBox::Escape,
                    0);
                msgBox->show();
            }
        }
        break;
    case edit:
        if(state==pause)
        {
            state=edit;
            cursor.setX(0);
            cursor.setY(0);
        }
        break;
    }
}

void SnakeGame::update1()
{
    snakes[0].update();
}

void SnakeGame::update2()
{
    snakes[1].update();
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    if(state==play)
    {
        if(snakes.size()>0)
        {
            switch (event->key()) {
            case Qt::Key_Up:
                snakes[0].turnDir(UP);
                break;
            case Qt::Key_Down:
                snakes[0].turnDir(DOWN);
                break;
            case Qt::Key_Right:
                snakes[0].turnDir(RIGHT);
                break;
            case Qt::Key_Left:
                snakes[0].turnDir(LEFT);
                break;
            default:
                break;
            }
        }
        if(snakes.size()>1)
        {
            switch (event->key()) {
            case Qt::Key_W:
                snakes[1].turnDir(UP);
                break;
            case Qt::Key_S:
                snakes[1].turnDir(DOWN);
                break;
            case Qt::Key_D:
                snakes[1].turnDir(RIGHT);
                break;
            case Qt::Key_A:
                snakes[1].turnDir(LEFT);
                break;
            default:
                break;
            }
        }
    }

    if(state==edit)
    {
        switch (event->key()) {
        case Qt::Key_Up:
            if(cursor.y()>0) cursor.ry()--;
            else cursor.setY(ROW);
            break;
        case Qt::Key_Down:
            if(cursor.y()<ROW) cursor.ry()++;
            else cursor.setY(0);
            break;
        case Qt::Key_Right:
            if(cursor.x()<COL) cursor.rx()++;
            else cursor.setX(0);
            break;
        case Qt::Key_Left:
            if(cursor.x()>0) cursor.rx()--;
            else cursor.setX(COL);
            break;
        case Qt::Key_L:
            if(isEmpty(cursor)) wall.push_back(cursor);
            else if(wall.contains(cursor)) wall.removeOne(cursor);
            break;
        case Qt::Key_F:
            if(isEmpty(cursor)) foods.push_back(Food(cursor.x(),cursor.y(),normal));
            else if(foods.contains(cursor)>=0) foods.removeAt(foods.contains(cursor));
            break;
        case Qt::Key_G:
            if(isEmpty(cursor)) foods.push_back(Food(cursor.x(),cursor.y(),speedup));
            else if(foods.contains(cursor)>=0) foods.removeAt(foods.contains(cursor));
            break;
        case Qt::Key_H:
            if(isEmpty(cursor)) foods.push_back(Food(cursor.x(),cursor.y(),speeddown));
            else if(foods.contains(cursor)>=0) foods.removeAt(foods.contains(cursor));
            break;
        case Qt::Key_J:
            if(isEmpty(cursor)) foods.push_back(Food(cursor.x(),cursor.y(),lifeplus));
            else if(foods.contains(cursor)>=0) foods.removeAt(foods.contains(cursor));
            break;
        case Qt::Key_K:
            if(isEmpty(cursor)) foods.push_back(Food(cursor.x(),cursor.y(),decline));
            else if(foods.contains(cursor)>=0) foods.removeAt(foods.contains(cursor));
            break;
        }
    }

    switch (event->key()) {
    case Qt::Key_P:
        if(state==play||state==pause)
            changeState(pause);
        break;
    case Qt::Key_E:
        if(state==pause)
            changeState(edit);
        else if(state==edit) changeState(pause);
        break;
    default:
        break;
    }
}

void SnakeGame::onePlay()
{
    snakenum=1;
    changeState(play);
}

void SnakeGame::twoPlay()
{
    snakenum=2;
    changeState(play);
}

void SnakeGame::clearInfo()
{
    disconnect(timer1,nullptr,this,nullptr);
    disconnect(timer2,nullptr,this,nullptr);
    if(timer1->isActive()) timer1->stop();
    if(timer2->isActive()) timer2->stop();
    if(!snakes.empty()) snakes.clear();
    if(!wall.empty()) wall.clear();
    if(!foods.empty()) foods.clear();    
    foods.cnt=0;
}

void SnakeGame::restart()
{
    changeState(play);
}

void SnakeGame::save()
{
    QFile file("resume.txt");
    if(file.open(QFile::WriteOnly|QIODevice::Truncate))
    {
        QTextStream out(&file);
        out<<snakenum<<endl;
        for(int i=0;i<snakenum;++i)
        {
            out<<snakes[i].life<<' '<<snakes[i].curdir<<' '<<snakes[i].speed<<' '<<snakes[i].length<<' '<<snakes[i].curInter<<endl;
            out<<snakes[i].size()<<endl;
            for (int j=0;j<snakes[i].size();++j)
            {
                out<<snakes[i][j].x()<<' '<<snakes[i][j].y()<<endl;
            }
        }

        out<<foods.size()<<endl;
        for(int i=0;i<foods.size();++i)
        {
            out<<foods[i].x()<<' '<<foods[i].y()<<' '<<foods[i].retType()<<endl;
        }

        out<<wall.size()<<endl;
        for(int i=0;i<wall.size();++i)
        {
            out<<wall[i].x()<<' '<<wall[i].y()<<endl;
        }
    }
    else qDebug()<<"Open file failed."<<endl;
}

void SnakeGame::resume()
{
    QFile file("resume.txt");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        int ssize,fsize,wsize;
        in>>snakenum;
        for (int i=0;i<snakenum;++i)
        {
            snakes.push_back(Snake(this));
            in>>snakes[i].life>>snakes[i].curdir>>snakes[i].speed>>snakes[i].length>>snakes[i].curInter;
            in>>ssize;
            for (int j=0;j<ssize;++j)
            {
                snakes[i].push_back(Point());
                in>>snakes[i][j].rx()>>snakes[i][j].ry();
            }
        }

        in>>fsize;
        for (int i=0;i<fsize;++i)
        {
            foods.push_back(Food());
            in>>foods[i].rx()>>foods[i].ry()>>foods[i].type;
        }

        in>>wsize;
        for (int i=0;i<wsize;++i)
        {
            wall.push_back(Point());
            in>>wall[i].rx()>>wall[i].ry();
        }
    }
    else qDebug()<<"Open file failed."<<endl;

    gameboard->show();
    infowindow->show();
    mainwindow->close();
    timer1->start(snakes[0].curInter);
    if(snakenum>1)
        timer2->start(snakes[1].curInter);
    connect(timer1,&QTimer::timeout,this,&SnakeGame::update1);
    if(snakenum>1) connect(timer2,&QTimer::timeout,this,&SnakeGame::update2);
    state=play;
}

void SnakeGame::Back()
{
    if(state!=over)
        save();
    clearInfo();
    changeState(menu);
}

bool SnakeGame::isEmpty(Point pt)
{
    for(int i=0;i<snakes.size();++i)
        if (snakes[i].contains(pt))
            return false;

    if(foods.contains(pt)>=0) return false;
    if(wall.contains(pt)) return  false;
    return true;
}

void SnakeGame::Edit()
{
    resume();
    changeState(pause);
    changeState(edit);
}

void SnakeGame::oneplayerSlot()
{
    onePlay();
}

void SnakeGame::twoplayerSlot()
{
    twoPlay();
}

void SnakeGame::editSlot()
{
    Edit();
}

void SnakeGame::resumeSlot()
{
    resume();
}
