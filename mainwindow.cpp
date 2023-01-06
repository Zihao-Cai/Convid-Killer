#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTime>
#include <ctime>

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
    map_timer.setInterval(10);
    ins_timer.setInterval(1000);
    tiptimer.setInterval(1000);
    ch_timer.setInterval(1000);
    p_timer.setInterval(60);
    e_timer.setInterval(120);
    eap_timer.setInterval(8000);//间隔八秒出现敌人
    choice_y[0] = 225;
    choice_y[1] = 225+60;
    choice_y[2] = 225+60*2;
    choice_y[3] = 225+60*3;
    choicey = 0;
    choice_x[0] = 63;
    choice_x[1] = 181;
    choice_x[2] = 299;
    choice_x[3] = 417;
    choicex = 0;
    myplanes[1] = QPixmap(":/p1.png");
    myplanes[2] = QPixmap(":/p2.png");
    myplanes[3] = QPixmap(":/p3.png");
    myplanes[4] = QPixmap(":/p4.png");//通过myplane的setpix()接口更换战机图片即可,从该数组中获取
    pool = new Bulpool();
    myplane = new Plane(this->pool);

    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);//屏蔽鼠标事件
    connect(&tiptimer,&QTimer::timeout,[=](){//菜单提示定时器
        if(tipflag){
            tipflag = false;
        }else{
            tipflag = true;
        }
        update();//mainwindow重绘函数
    });
    connect(&ins_timer,&QTimer::timeout,[=](){//操作说明提示定时器
        if(insflag){
            insflag = false;
        }else{
            insflag = true;
        }
        update();
    });
    connect(&map_timer,&QTimer::timeout,[=](){//地图背景滚动定时器
        recalc();
        update();
    });
    connect(&p_timer,&QTimer::timeout,[=](){//战机移动定时器
        myplane->move(myplane->dir);
        update();
    });
    connect(&e_timer,&QTimer::timeout,[=](){//敌人移动射击定时器
        srand((unsigned int) time(NULL));
        for(int i=0;i<enemys.size();i++){
            int tempdir = rand()%100;
            int flag = rand()%10;
            enemys[i].move(tempdir);
            update();
            enemys[i].shoot(flag);
            update();
        }
    });
    connect(&eap_timer,&QTimer::timeout,[=](){//敌人出现定时器
        Enemy te = Enemy();
        te.state = 1;
        enemys.push_back(te);
        update();
    });
    connect(&ch_timer,&QTimer::timeout,[=](){//换机提示定时器
        if(chflag){
            chflag = false;
        }else{
            chflag = true;
        }
        update();
    });



    menu();
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(status == GAME){
        painter.drawPixmap(0,map.mapy1,map.map_1);
        painter.drawPixmap(0,map.mapy2,map.map_2);//绘制地图背景
        painter.drawPixmap(myplane->x,myplane->y,myplane->pix_plane);//绘制我方战机
        for(int i=0;i<myplane->mybuls.size();i++){
            painter.drawPixmap(myplane->mybuls[i].x,myplane->mybuls[i].y,myplane->mybuls[i].bul_pix);
        }//绘制我方子弹
        for(int i=0;i<enemys.size();i++){
            painter.drawPixmap(enemys[i].x,enemys[i].y,enemys[i].pix_plane);
            for(int j=0;j<enemys[i].enbuls.size();j++){
                painter.drawPixmap(enemys[i].enbuls[j].x,enemys[i].enbuls[j].y,enemys[i].enbuls[j].bul_pix);
            }//绘制敌人子弹
        }//绘制敌人


    }
    if(status == MENU){
        painter.drawPixmap(0,0,QPixmap(":/xingyun1.jpg"));
        QPixmap pixmap(":/choice.png");
        QPixmap fitpixmap = pixmap.scaled(100, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(90,choice_y[choicey],fitpixmap);
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
        painter.drawPixmap(0,0,QPixmap(":/xingyun1.jpg"));
        painter.setPen(Qt::red);
        QFont textfont;
        textfont.setPixelSize(16);//字体大小
        textfont.setBold(true);//设置加粗
        painter.setFont(textfont);
        painter.drawText(120,330,"A、D键控制战机左右移动,J键发射子弹");
        painter.drawText(90,370,"按P键暂停游戏,按下Esc键停止游戏返回菜单");
        QPixmap messageOK(":/messageOK.png");
        messageOK = messageOK.scaled(100, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(insflag){
            painter.drawPixmap(200,400,messageOK);
            painter.drawText(210,460,"按J键确认");
        }

    }

    if(status == CHANGEIP){
        painter.setPen(Qt::red);
        QFont textfont;
        textfont.setPixelSize(16);//字体大小
        textfont.setBold(true);//设置加粗
        painter.setFont(textfont);
        painter.drawPixmap(0,0,QPixmap(":/xingyun1.jpg"));
        for(int i=1;i<5;i++){//绘制可选战机
            QPixmap pi = myplanes[i].scaled(80,80, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(38*i+(i-1)*80,300,pi);
        }
        QPixmap pixmap(":/choice_x.png");
        pixmap = pixmap.scaled(30, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(choice_x[choicex],390,pixmap);
        QPixmap messageOK(":/messageOK.png");
        messageOK = messageOK.scaled(100, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        if(chflag){
            painter.drawPixmap(200,500,messageOK);
            painter.drawText(170,560,"A、D键选择,J键确认");
        }


    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(status == MENU){
    if(event->key() == Qt::Key_W){
        choicey = (choicey-1)%4;
        if(choicey<0){
            choicey = 3;
        }
    }
    if(event->key() == Qt::Key_S){
        choicey = (choicey+1)%4;
    }
    if(event->key() == Qt::Key_J){
        switch (choicey) {
        case 0: startgame();break;
        case 1: changeip();break;
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
    if(status == GAME){
        switch (event->key()) {
        case Qt::Key_W:myplane->dir = 0;break;
        case Qt::Key_S:myplane->dir = 2;break;
        case Qt::Key_A:myplane->dir = 3;break;
        case Qt::Key_D:myplane->dir = 1;break;
        }
        if(event->key() == Qt::Key_J){
            myplane->shoot();
        }
        if(event->key() == Qt::Key_Escape){//结束游戏返回菜单
            menu();
        }
        if(event->key() == Qt::Key_P){
            gamepause();
        }

        update();
        return;
    }

    if(status == CHANGEIP){
        if(event->key() == Qt::Key_A){
            choicex = (choicex-1)%4;
            if(choicex<0){
                choicex = 3;
            }
        }
        if(event->key() == Qt::Key_D){
            choicex = (choicex+1)%4;
        }
        if(event->key() == Qt::Key_J){
            switch (choicex) {
            case 0: myplane->setpix(myplanes[1]);break;
            case 1: myplane->setpix(myplanes[2]);break;
            case 2: myplane->setpix(myplanes[3]);break;
            case 3: myplane->setpix(myplanes[4]);break;
            }
            //这里后期做一个更换成功的提示
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
    myplane->setpos((WIDTH-RECT_WIDTH)/2,HEIGHT - RECT_HEIGHT);//设置战机起始位置
    enemys.clear();//清空所有敌人
    myplane->mybuls.clear();//清空所有子弹
    map_timer.start();
    ins_timer.stop();
    tiptimer.stop();
    p_timer.start();
    e_timer.start();
    eap_timer.start();
}

void MainWindow::recalc()
{
    map.mapposition();
    for(int i=0;i<myplane->mybuls.size();i++){
        if(myplane->mybuls[i].state == 2 || myplane->mybuls[i].islive == 0){
            myplane->mybuls.remove(i);
        }else{
            myplane->mybuls[i].bul_recalc(0);
        }
    }
    for(int i=0;i<enemys.size();i++){
        if(enemys[i].state == 2 || enemys[i].islive == 0){
            enemys.remove(i);
        }else{
            for(int j=0;j<enemys[i].enbuls.size();j++){
                if(enemys[i].enbuls[j].state == 2 || enemys[i].enbuls[j].islive == 0){
                    enemys[i].enbuls.remove(j);
                }else{
                enemys[i].enbuls[j].bul_recalc(2);
                }
          }
        }
    }
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
    ins_timer.start();
    tiptimer.stop();
    map_timer.stop();
    p_timer.stop();
    e_timer.stop();
    eap_timer.stop();
}

void MainWindow::menu()
{
    status = MENU;
    tiptimer.start();
    map_timer.stop();
    ins_timer.stop();
    p_timer.stop();
    e_timer.stop();
    eap_timer.stop();
    for(int i=0;i<menu_btn.size();i++){//显示菜单
        menu_btn[i]->show();
    }
}

void MainWindow::gamepause()
{
    printf("game-pause!\n");
}

void MainWindow::changeip()
{
    status = CHANGEIP;
    hidemenu();
    tiptimer.stop();
    map_timer.stop();
    ins_timer.stop();
    p_timer.stop();
    e_timer.stop();
    ch_timer.start();
    eap_timer.stop();
}





