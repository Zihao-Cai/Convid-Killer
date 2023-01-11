#include "enemy.h"
#include <QTime>

Enemy::Enemy()
{
    state = 0;
    blood = 1;
    isbingdu = false;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int pixindex = qrand()%5;
    QPixmap pix;
    switch (pixindex) {
    case 0:pix.load(":/e1.png");break;
    case 1:pix.load(":/e2.png");break;
    case 2:pix.load(":/e3.png");break;
    case 3:pix.load(":/bingdu1.png");break;
    case 4:pix.load(":/bingdu1.png");break;
    }
    pix = pix.scaled(RECT_WIDTH,RECT_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pix_plane = pix;

    int pos_x = qrand()%453;
    int pos_y = -RECT_HEIGHT;
    x = pos_x;
    y = pos_y;
    dir = 2;
    speed = MYSPEED;
    rect.setRect(this->x,this->y,RECT_WIDTH,RECT_HEIGHT);
    shot_intv = 0;
    if(pixindex == 3 ||pixindex == 4){
        isbingdu = true;
        speed += 2;
    }//病毒体做特殊构造
}

void Enemy::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
    this->rect.setRect(x,y,RECT_WIDTH,RECT_HEIGHT);
}

void Enemy::setpix(QPixmap pix)
{
    pix = pix.scaled(RECT_WIDTH,RECT_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pix_plane = pix;
}

void Enemy::shoot(int flag)
{
    if(flag == 0 && this->y>=0){
        shot_intv++;
    }
    if(shot_intv == 2 && isbingdu == false){
        Bullet tempbul(this->x,this->y,2,false);
        tempbul.state = 1;
        enbuls.push_back(tempbul);
        shot_intv = 0;
    }
}

void Enemy::move(int tempdir)
{

    if(tempdir<10){
        dir = 0;
    }
    if(10<=tempdir && tempdir<30){
        dir = 1;
    }
    if(tempdir>=30 && tempdir<50){
        dir = 2;
    }
    if(tempdir>=50 && tempdir<70){
        dir = 3;
    }
    if(y<=0){
        dir = 2;
    }
    switch (dir) {
    case 0:if((y-speed)>=-RECT_HEIGHT){y -= speed;}break;
    case 1:if((x+RECT_WIDTH+speed)<=WIDTH){x += speed;}break;
    case 2:y += speed;break;
    case 3:if((x-speed)>=0){x -= speed;}break;
    }
    if(y>=HEIGHT){
        state = 2;
    }
    rect.setRect(this->x,this->y,RECT_WIDTH,RECT_HEIGHT);
}


