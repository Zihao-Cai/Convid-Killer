#include "bombcartoon.h"
#include <QString>
#include "config.h"

Bombcartoon::Bombcartoon()
{
    for(int i = 1;i<=5;i++){
        QString str = QString(":/bomb-%1.png").arg(i);
        setpix(QPixmap(str));
    }
    x = -RECT_WIDTH;
    y = -RECT_HEIGHT;
    state = 0;
    pix_index = 0;
    interval = 0;
}

void Bombcartoon::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Bombcartoon::setpix(QPixmap pix)
{
    pix = pix.scaled(RECT_WIDTH/2,RECT_HEIGHT/2 , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->bombpix.push_back(pix);
}

void Bombcartoon::calc()
{
    if(state != 1){
        return;
    }
    interval++;
    if(interval<20){
        return;
    }
    interval = 0;
    pix_index++;
    if(pix_index >= 5){
        pix_index = 0;
        state = 2;
    }
}
