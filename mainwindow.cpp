#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTime>
#include <ctime>
#include <math.h>

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
    game_timers.push_back(map_timer);
    game_timers.push_back(p_timer);
    game_timers.push_back(e_timer);
    game_timers.push_back(eap_timer);
    game_timers.push_back(ell_timer);
    game_timers.push_back(item_timer);
    game_timers.push_back(itemflash_timer);

    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle(GAME_TITLE);
    QPixmap img(":/icon.jpg");
    QIcon icon = QIcon(img);
    setWindowIcon(icon);

    map_timer->setInterval(10);
    ins_timer.setInterval(1000);
    tiptimer.setInterval(1000);
    ch_timer.setInterval(1000);
    ell_timer->setInterval(1000);
    p_timer->setInterval(60);
    e_timer->setInterval(120);
    eap_timer->setInterval(8000);//间隔八秒出现敌人
    item_timer->setInterval(5000);//间隔15秒可能出现道具
    itemflash_timer->setInterval(400);

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
    myplane = new Plane();
    menu_bgm = new QSound(":/menu_music.wav");
    game_bgm = new QSound(":/game_music.wav");
    choose_bgm = new QSound(":/choose_music.wav");
    config_bgm = new QSound(":/config.wav");
    shoot_bgm = new QSound(":/shoot.wav");
    getitem_bgm = new QSound(":/getitem.wav");
    bomb_bgm = new QSound(":/bomb.wav");
    score = 0;

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
    connect(map_timer,&QTimer::timeout,[=](){//地图背景滚动定时器
        recalc();
        update();
    });
    connect(p_timer,&QTimer::timeout,[=](){//战机移动定时器

        myplane->move(myplane->dir);
        update();
    });
    connect(e_timer,&QTimer::timeout,[=](){//敌人移动射击定时器//道具移动定时器

        srand((unsigned int) time(NULL));
        for(int i=0;i<enemys.size();i++){
            int tempdir = rand()%100;
            int flag = rand()%10;
            enemys[i].move(tempdir);
            enemys[i].shoot(flag);
        }
        for(int i=0;i<items.size();i++){
            int flag = rand()%5;
            if(flag == 0){
                items[i].move();
            }
        }
    });
    connect(eap_timer,&QTimer::timeout,[=](){//敌人出现定时器
        Enemy te = Enemy();
        te.state = 1;
        if(enemys.size()<6){
            enemys.push_back(te);
        }
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
    connect(ell_timer,&QTimer::timeout,[=](){//圆周绘制定时器
        if(ellflag){
            ellflag = false;
        }else{
            ellflag = true;
        }
        update();
    });
    connect(item_timer,&QTimer::timeout,[=](){//加成道具定时器
        int flag = rand()%3;
        if(flag == 0){
            Plusitem item;
            item.state = 1;
            item.settime(QDateTime::currentDateTime());
            items.push_back(item);
        }
        update();
    });
    connect(itemflash_timer,&QTimer::timeout,[=](){//道具闪烁定时器
        if(itemflash){
            itemflash = false;
        }else{
            itemflash = true;
        }
        update();
    });



    menu();
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(status == GAME){

        if(game_bgm->isFinished()){
            gamebgm_ch();
            game_bgm->play();
        }//游戏战斗音乐
        painter.drawPixmap(0,map->mapy1,map->map_1);
        painter.drawPixmap(0,map->mapy2,map->map_2);//绘制地图背景
        painter.drawPixmap(myplane->x,myplane->y,myplane->pix_plane);//绘制我方战机
        for(int i=0;i<myplane->mybuls.size();i++){
            painter.drawPixmap(myplane->mybuls[i].x,myplane->mybuls[i].y,myplane->mybuls[i].bul_pix);
        }//绘制我方子弹
        for(int i=0;i<enemys.size();i++){
            painter.drawPixmap(enemys[i].x,enemys[i].y,enemys[i].pix_plane);
            if(enemys[i].isbingdu && ellflag){
                painter.setPen(Qt::red);//设置画笔,绘制圆周颜色
                painter.drawEllipse(enemys[i].x-30,enemys[i].y-30,120,120);
            }
            for(int j=0;j<enemys[i].enbuls.size();j++){
                painter.drawPixmap(enemys[i].enbuls[j].x,enemys[i].enbuls[j].y,enemys[i].enbuls[j].bul_pix);
            }//绘制敌人子弹
        }//绘制敌人
        for(int i=0;i<cartoons.size();i++){
            painter.drawPixmap(cartoons[i].x,cartoons[i].y,cartoons[i].bombpix[cartoons[i].pix_index]);
        }//绘制爆炸动画
        for(int i=0;i<items.size();i++){
            if(items[i].birth_time.secsTo(QDateTime::currentDateTime())<12){
                painter.drawPixmap(items[i].x,items[i].y,items[i].pix);
            }else{
                if(itemflash)   painter.drawPixmap(items[i].x,items[i].y,items[i].pix);
            }
        }//绘制加成道具
        QFont textfont;
        textfont.setPixelSize(12);
        textfont.setBold(true);
        textfont.setLetterSpacing(QFont::AbsoluteSpacing,10);
        painter.setFont(textfont);
        painter.setPen(Qt::green);
        QString str;
        if(myplane->isup){
            str = QString("血量:")+QString::number(myplane->blood)+" "+QString("导弹:已强化")+"   "+QString("得分:")+QString::number(score);
        }else{
            str = QString("血量:")+QString::number(myplane->blood)+" "+QString("导弹:未强化")+"   "+QString("得分:")+QString::number(score);
        }
        painter.drawText(0,765,str);//绘制底部状态信息



    }
    if(status!= GAME){
        if(menu_bgm->isFinished()){
            menubgm_ch();
            menu_bgm->play();
        }
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
        painter.drawText(110,300,"W、S、A、D键控制战机移动,J键发射子弹");
        painter.drawText(70,320,"病毒体无法射击但拥有更快移动速度并且会范围爆炸");
        painter.drawText(110,340,"游戏内拾取道具可获得血量和导弹加成");
        painter.drawText(90,360,"按P键暂停游戏,按下Esc键结束游戏返回菜单");
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
        choose_bgm->play();
        choicey = (choicey-1)%4;
        if(choicey<0){
            choicey = 3;
        }
    }
    if(event->key() == Qt::Key_S){
        choose_bgm->play();
        choicey = (choicey+1)%4;
    }
    if(event->key() == Qt::Key_J){
        config_bgm->play();
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
            config_bgm->play();
            menu();
        }
        update();
        return;
    }
    if(status == GAME && !pause){
        switch (event->key()) {
        case Qt::Key_W:myplane->dir = 0;break;
        case Qt::Key_S:myplane->dir = 2;break;
        case Qt::Key_A:myplane->dir = 3;break;
        case Qt::Key_D:myplane->dir = 1;break;
        }
        if(event->key() == Qt::Key_J){
            shoot_bgm->play();
            if(myplane->isup){
                myplane->shoot(true);
                myplane->isup = false;
            }else{
                myplane->shoot(false);
            }
        }
        if(event->key() == Qt::Key_Escape){//结束游戏返回菜单
            menu();
        }
        if(event->key() == Qt::Key_P){//暂停游戏
            gamepause();
        }

        update();
        return;
    }
    if(status == GAME && pause){
        if(event->key() == Qt::Key_P){
            gamerecov();
        }
        if(event->key() == Qt::Key_Escape){
            menu();
        }
    }

    if(status == CHANGEIP){
        if(event->key() == Qt::Key_A){
            choose_bgm->play();
            choicex = (choicex-1)%4;
            if(choicex<0){
                choicex = 3;
            }
        }
        if(event->key() == Qt::Key_D){
            choose_bgm->play();
            choicex = (choicex+1)%4;
        }
        if(event->key() == Qt::Key_J){
            config_bgm->play();
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
    myplane->state = 1;//重置战机状态
    enemys.clear();//清空所有敌人
    myplane->mybuls.clear();//清空所有子弹
    cartoons.clear();//清空所有动画
    map = new Map();//重置地图，达到游戏内随机切换地图效果
    score = 0;//重置得分
    myplane->blood = 1;//重置玩家血量
    myplane->isup = false;//重置强化导弹
    map_timer->start();
    ins_timer.stop();
    tiptimer.stop();
    p_timer->start();
    e_timer->start();
    eap_timer->start();
    ell_timer->start();
    item_timer->start();
    itemflash_timer->start();
    //bgm播放
    menu_bgm->stop();
    if(game_bgm->isFinished()){
        game_bgm->play();
    }
}

void MainWindow::recalc()
{
    isbomb();
    isitem();
    map->mapposition();
    for(int i=0;i<myplane->mybuls.size();i++){
        if(myplane->mybuls[i].state == 2){
            myplane->mybuls.remove(i);
        }else{
            myplane->mybuls[i].bul_recalc(0);
        }
    }
    for(int i=0;i<enemys.size();i++){
        if(enemys[i].state == 2){
            enemys.remove(i);
        }else{
            for(int j=0;j<enemys[i].enbuls.size();j++){
                if(enemys[i].enbuls[j].state == 2){
                    enemys[i].enbuls.remove(j);
                }else{
                enemys[i].enbuls[j].bul_recalc(2);
                }
          }
        }
    }
    for(int i=0;i<cartoons.size();i++){
        if(cartoons[i].state != 1){
            cartoons.remove(i);
        }else{
            cartoons[i].calc();
        }
    }
    for(int i=0;i<items.size();i++){
        if(items[i].state != 1 || items[i].birth_time.secsTo(QDateTime::currentDateTime())>14){
            items.remove(i);
        }
    }

    if(myplane->blood <= 0){
        printf("game-over!\n");
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
    map_timer->stop();
    p_timer->stop();
    e_timer->stop();
    eap_timer->stop();
}

void MainWindow::menu()
{
    status = MENU;
    tiptimer.start();
    map_timer->stop();
    ins_timer.stop();
    p_timer->stop();
    e_timer->stop();
    eap_timer->stop();
    for(int i=0;i<menu_btn.size();i++){//显示菜单
        menu_btn[i]->show();
    }
    game_bgm->stop();
    if(menu_bgm->isFinished()){
        menu_bgm->play();
    }
}

void MainWindow::gamepause()
{
    pause = true;
    pause_time = QDateTime::currentDateTime();
    printf("game-pause!\n");
    for(int i=0;i<game_timers.size();i++){
        game_timers[i]->stop();
    }
    myplane->tempdir = myplane->dir;
    myplane->dir = -1;

}

void MainWindow::gamerecov()
{
    pause = false;
    pause_time = QDateTime::currentDateTime();
    printf("game-recov!\n");
    for(int i=0;i<game_timers.size();i++){
        game_timers[i]->start();
    }
    myplane->dir = myplane->tempdir;
}

void MainWindow::changeip()
{
    status = CHANGEIP;
    hidemenu();
    tiptimer.stop();
    map_timer->stop();
    ins_timer.stop();
    p_timer->stop();
    e_timer->stop();
    ch_timer.start();
    eap_timer->stop();
}

void MainWindow::isbomb()
{
    for(int i=0;i<myplane->mybuls.size();i++){//我方子弹与敌人的碰撞检测
        for(int j=0;j<enemys.size();j++){
            if(myplane->mybuls[i].bul_rect.intersects(enemys[j].rect)){
                if(!myplane->mybuls[i].isup)    myplane->mybuls[i].state = 2;
                enemys[j].state = 2;
                Bombcartoon c;
                c.setpos(enemys[j].x+RECT_WIDTH/4,enemys[j].y+RECT_HEIGHT/4);
                c.state = 1;
                cartoons.push_back(c);
                bomb_bgm->play();
                score++;
                update();
            }

        }
    }
    //敌人子弹与我方战机的碰撞检测
    for(int i=0;i<enemys.size();i++){
        for(int j = 0;j<enemys[i].enbuls.size();j++){
            if(enemys[i].enbuls[j].bul_rect.intersects(myplane->rect)){
                enemys[i].enbuls[j].state = 2;
                Bombcartoon c;
                c.setpos(myplane->x+RECT_WIDTH/4,myplane->y+RECT_HEIGHT/4);
                c.state = 1;
                cartoons.push_back(c);
                bomb_bgm->play();
                myplane->blood--;
                update();
            }
        }
    }
    //我方子弹与敌方子弹的碰撞检测
    for(int i=0;i<myplane->mybuls.size();i++){
        for(int j=0;j<enemys.size();j++){
            for(int k=0;k<enemys[j].enbuls.size();k++){
                if(myplane->mybuls[i].bul_rect.intersects(enemys[j].enbuls[k].bul_rect)){
                    Bombcartoon c;
                    c.setpos(myplane->mybuls[i].x,myplane->mybuls[i].y);
                    c.state = 1;
                    cartoons.push_back(c);
                    if(!myplane->mybuls[i].isup)    {myplane->mybuls[i].state = 2;}
                    enemys[j].enbuls[k].state = 2;
                    update();
                }
            }
        }
    }
    //病毒体和我方战机的碰撞检测
    for(int i=0;i<enemys.size();i++){
        if(enemys[i].isbingdu){
            if(bingdu_collapse(myplane->rect,enemys[i].rect)){
                Bombcartoon c1,c2;
                c1.setpos(myplane->x+RECT_WIDTH/4,myplane->y+RECT_HEIGHT/4);
                c2.setpos(enemys[i].x+RECT_WIDTH/4,enemys[i].y+RECT_HEIGHT/4);
                c1.state = 1;
                c2.state = 1;
                cartoons.push_back(c1);
                cartoons.push_back(c2);
                bomb_bgm->play();
                enemys[i].state = 2;
                myplane->blood = 0;
                update();
            }
        }
    }



}

void MainWindow::isitem()
{
    for(int i=0;i<items.size();i++){
        if(items[i].rect.intersects(myplane->rect)){
            if(items[i].type == ITEM_BLOOD){
                if(myplane->blood<3){
                    myplane->blood++;
                }
                getitem_bgm->play();
                items.remove(i);
                continue;
            }
            if(items[i].type == ITEM_UPGRADE){
                myplane->isup = true;
                getitem_bgm->play();
                items.remove(i);
                continue;
            }
        }
    }
    update();
}

void MainWindow::menubgm_ch()
{
    if(menu_bgm->fileName() == ":/menu_music.wav"){
        menu_bgm = new QSound(":/menu_2.wav");
    }else{
        menu_bgm = new QSound(":/menu_music.wav");
    }
}

void MainWindow::gamebgm_ch()
{
    if(game_bgm->fileName() == ":/game_music.wav"){
        game_bgm = new QSound(":/game_2.wav");
    }else{
        game_bgm = new QSound(":/game_music.wav");
    }
}

bool MainWindow::bingdu_collapse(QRect plane_rect, QRect bingdu_rect)
{
    //此碰撞检测为矩形和圆的相交问题,该问题分为两个分支检测//注意:bingdu_rect是enemy的矩形,而非圆的外接矩形

    //获取矩形和圆的必要参数
    int x1 = plane_rect.x();                    /*矩形左下顶点*/
    int y1 = plane_rect.y()+plane_rect.height();
    int x2 = plane_rect.x()+plane_rect.width(); /*矩形右上顶点*/
    int y2 = plane_rect.y();
    int r = 60;                                 /*圆半径*/
    int cx = bingdu_rect.x()+RECT_WIDTH/2;      /*圆心*/
    int cy = bingdu_rect.y()+RECT_HEIGHT/2;

    /*1:矩形某一个顶点进入圆内*/
    int minx,miny;
    if(abs(x1 - cx)<abs(x2 - cx)){
        minx = abs(x1 - cx);
    }else{
        minx = abs(x2 - cx);
    }
    if(abs(y1 - cy)<abs(y2 - cy)){
        miny = abs(y1 - cy);
    }else{
        miny = abs(y2 - cy);
    }
    if (minx * minx + miny * miny < r * r)  return true;

    /*2:矩形某一边与圆相交*/
    int x0 = (x1+x2)/2;                         /*矩形中心*/
    int y0 = (y1+y2)/2;
    if ((abs(x0 - cx) < abs(x2 - x1) / 2 + r) && abs(cy - y0) < abs(y2 - y1) / 2)
            return true;
        if ((abs(y0 - cy) < abs(y2 - y1) / 2 + r) && abs(cx - x0) < abs(x2 - x1) / 2)
            return true;


    return false;
}





