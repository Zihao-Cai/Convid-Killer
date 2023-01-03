#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initutil();//初始化



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initutil()
{
    menu_btn.push_back(ui->start);
    menu_btn.push_back(ui->change);
    menu_btn.push_back(ui->records);
    menu_btn.push_back(ui->exit);
    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle(GAME_TITLE);
    QPixmap img(":/icon.jpg");
    QIcon icon = QIcon(img);
    setWindowIcon(icon);
    timer.setInterval(10);
    status = MENU;
    choice_y[0] = 225;
    choice_y[1] = 225+60;
    choice_y[2] = 225+60*2;
    choice_y[3] = 225+60*3;
    choice = 0;
    //屏蔽鼠标事件
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);


    tiptimer.setInterval(1000);
    tiptimer.start();
    connect(&tiptimer,&QTimer::timeout,[=](){
        if(tipflag){
            tipflag = false;
        }else{
            tipflag = true;
        }
        update();
    });


}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(status == GAME){
        tiptimer.stop();
        ins_timer.stop();

        painter.drawPixmap(0,map.mapy1,map.map_1);
        painter.drawPixmap(0,map.mapy2,map.map_2);
    }
    if(status == MENU){
        timer.stop();
        ins_timer.stop();

        painter.drawPixmap(0,0,QPixmap(":/xingyun1.jpg"));
        QPixmap pixmap(":/choice.png");
        QPixmap fitpixmap = pixmap.scaled(100, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(90,choice_y[choice],fitpixmap);
        QFont textfont;
        textfont.setPixelSize(20);//字体大小
        textfont.setBold(true);//设置加粗
        textfont.setLetterSpacing(QFont::AbsoluteSpacing,10);//设置字符间距
        painter.setFont(textfont);
        painter.setPen(Qt::red);
        if(tipflag){
        painter.drawText(120,550,"W、S键选择,J键确认");
        }
    }
    if(status == INSTRUCTION){
        tiptimer.stop();
        timer.stop();

        painter.drawPixmap(0,0,QPixmap(":/xingyun1.jpg"));
        painter.setPen(Qt::red);
        QFont textfont;
        textfont.setPixelSize(16);//字体大小
        textfont.setBold(true);//设置加粗
        painter.setFont(textfont);
        painter.drawText(120,330,"A、D键控制战机左右移动,J键发射子弹");
        painter.drawText(90,370,"空格键暂停游戏,按下Esc键停止游戏返回菜单");
        QPixmap messageOK(":/messageOK.png");
        messageOK = messageOK.scaled(100, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(tipflag){
            painter.drawPixmap(200,400,messageOK);
            painter.drawText(210,460,"按J键确认");
        }

    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(status == MENU){
    if(event->key() == Qt::Key_W){
        choice = (choice-1)%4;
        if(choice<0){
            choice = 3;
        }
    }
    if(event->key() == Qt::Key_S){
        choice = (choice+1)%4;
    }
    if(event->key() == Qt::Key_J){
        switch (choice) {
        case 0: startgame();break;
        case 1: ;break;
        case 2: instruction();break;
        case 3: this->close();
        }
    }
    update();
    return;
}
    if(status == INSTRUCTION){
        if(event->key() == Qt::Key_J){
            menu();
        }
        update();
        return;
    }



}

void MainWindow::startgame()
{
    hidemenu();
    status = GAME;
    timer.start();
    connect(&timer,&QTimer::timeout,[=](){
        recalc();
        update();//重绘函数
    });
}

void MainWindow::recalc()
{
    map.mapposition();
}

void MainWindow::hidemenu()
{
    for(int i=0;i<menu_btn.size();i++){
        menu_btn[i]->hide();
    }
}

void MainWindow::instruction()
{
    status = INSTRUCTION;
    hidemenu();
    ins_timer.setInterval(1000);
    ins_timer.start();
    connect(&ins_timer,&QTimer::timeout,[=](){
        if(tipflag){
            tipflag = false;
        }else{
            tipflag = true;
        }
        update();
    });
}

void MainWindow::menu()
{
    status = MENU;
    tiptimer.start();
    for(int i=0;i<menu_btn.size();i++){
        menu_btn[i]->show();
    }
}





