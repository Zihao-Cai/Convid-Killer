#include "radiation.h"
#include <QDebug>

Radiation::Radiation(int par_x,int par_y)
{

    birth_time = QDateTime::currentDateTime();
    //qDebug()<<birth_time<<endl;
    pix = QPixmap(":/radi.png");
    this->x = par_x+RECT_WIDTH/2-RADI_WIDTH/2;
    this->y = par_y+RECT_HEIGHT;
    this->rect.setRect(x,y,RADI_WIDTH,HEIGHT-y);
    update_pos(par_x,par_y);
}

void Radiation::update_pos(int par_x,int par_y)
{
    this->x = par_x+RECT_WIDTH/2-RADI_WIDTH/2;
    this->y = par_y+RECT_HEIGHT;
    pix = pix.scaled(RADI_WIDTH,HEIGHT-this->y , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->rect.setRect(x,y,RADI_WIDTH,HEIGHT-y);
}
