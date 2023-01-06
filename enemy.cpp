#include "enemy.h"
#include <QTime>

Enemy::Enemy()
{
    islive = 1;
    state = 0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int pixindex = qrand()%4;
    QPixmap pix;
    switch (pixindex) {
    case 0:pix.load(":/e1.png");break;
    case 1:pix.load(":/e2.png");break;
    case 2:pix.load(":/e3.png");break;
    case 3:pix.load(":/bingdu1.png");break;
    }
    pix = pix.scaled(RECT_WIDTH,RECT_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pix_plane = pix;
    if(pixindex == 3){
        //-->病毒无法发射子弹
        //-->病毒拥有更大打击范围,方式为自爆,做圆周范围自爆检测
        //-->病毒自爆圆周绘制图形显示范围
    }//病毒体做特殊构造
    int pos_x = qrand()%453;
    int pos_y = -RECT_HEIGHT;
    x = pos_x;
    y = pos_y;
    dir = 2;
    rect.setRect(this->x,this->y,RECT_WIDTH,RECT_HEIGHT);
    shot_intv = 0;
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
    if(shot_intv == 2){
        Bullet tempbul(this->x,this->y,2);
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
    case 0:if((y-MYSPEED)>=-RECT_HEIGHT){y -= MYSPEED;}break;
    case 1:if((x+RECT_WIDTH+MYSPEED)<=WIDTH){x += MYSPEED;}break;
    case 2:y += MYSPEED;break;
    case 3:if((x-MYSPEED)>=0){x -= MYSPEED;}break;
    }
    if(y>=HEIGHT){
        state = 2;
    }
}
