#include "plane.h"
#include "bullet.h"


Plane::Plane()
{
    state = 1;
    blood = 1;
    isup = false;
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

void Plane::shoot(bool up)
{
    //新开一个子弹对象装载
    Bullet tempbul(this->x,this->y,0,up);
    tempbul.state = 1;
    mybuls.push_back(tempbul);
}

void Plane::move(int dir)
{
    switch (dir) {
    case 0:if((y-MYSPEED)>=0){y -= MYSPEED;}break;
    case 1:if((x+RECT_WIDTH+MYSPEED)<=WIDTH){x += MYSPEED;}break;
    case 2:if((y+RECT_HEIGHT+MYSPEED)<=HEIGHT){y += MYSPEED;}break;
    case 3:if((x-MYSPEED)>=0){x -= MYSPEED;}break;
    }
    rect.setRect(this->x,this->y,RECT_WIDTH,RECT_HEIGHT);
}
