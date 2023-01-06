#include "plane.h"
#include "bullet.h"


Plane::Plane(Bulpool* pool)
{
    islive = 1;
    this->pool = pool;
    QPixmap pix(":/p1.png");
    pix = pix.scaled(RECT_WIDTH,RECT_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pix_plane = pix;
    x = (WIDTH-RECT_WIDTH)/2;
    y = HEIGHT - RECT_HEIGHT;
    dir = 1;
    rect.setRect(this->x,this->y,RECT_WIDTH,RECT_HEIGHT);

}

void Plane::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
    this->rect.setRect(x,y,RECT_WIDTH,RECT_HEIGHT);
}

void Plane::setpix(QPixmap pix)
{
    pix = pix.scaled(RECT_WIDTH,RECT_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pix_plane = pix;
}

void Plane::shoot()
{
    int i = 0;
    for(i=0;i<BULPOOLSIZE;i++){
        if(pool->bulpool[i].state == 0){
            pool->bulpool[i].setpos(this->x+RECT_WIDTH/2-MYBUL_WIDTH/2,this->y-MYBUL_HEIGHT);
            pool->bulpool[i].state = 1;
            mybuls.push_back(pool->bulpool[i]);
            break;
        }
    }
    //若子弹池没有空闲子弹,则新开一个子弹对象装载
    if(i == BULPOOLSIZE){
        Bullet tempbul(this->x,this->y,0);
        tempbul.state = 1;
        mybuls.push_back(tempbul);
    }
}

void Plane::move(int dir)
{
    switch (dir) {
    case 0:if((y-MYSPEED)>=0){y -= MYSPEED;}break;
    case 1:if((x+RECT_WIDTH+MYSPEED)<=WIDTH){x += MYSPEED;}break;
    case 2:if((y+RECT_HEIGHT+MYSPEED)<=HEIGHT){y += MYSPEED;}break;
    case 3:if((x-MYSPEED)>=0){x -= MYSPEED;}break;
    }

}
