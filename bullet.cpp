#include "bullet.h"
#include "config.h"

Bullet::Bullet(int par_x,int par_y,int dir,bool up)
{
    if(dir == 0){
        x = par_x+RECT_WIDTH/2-MYBUL_WIDTH/2;
        y = par_y-MYBUL_HEIGHT;
    }
    if(dir == 2){
        x = par_x+RECT_WIDTH/2-MYBUL_WIDTH/2;
        y = par_y+RECT_HEIGHT;
    }
    state = 0;
    p_speed = 4;
    e_speed = 3;
    QPixmap pix;
    if(dir == 0){
        pix.load(":/bullet2.png");
    }
    if(dir == 2){
        pix.load(":/bullet2_.png");
    }
    if(up){
        pix.load(":/bullet1.png");
        isup = true;
    }
    bul_pix = pix.scaled(MYBUL_WIDTH,MYBUL_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    bul_rect.setRect(this->x,this->y,MYBUL_WIDTH,MYBUL_HEIGHT);
}

Bullet::Bullet()
{
    x = -100;
    y = -100;
    state = 0;
    p_speed = 4;
    e_speed = 3;
    QPixmap pix(":/bullet2.png");
    bul_pix = pix.scaled(MYBUL_WIDTH,MYBUL_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    bul_rect.setRect(this->x,this->y,MYBUL_WIDTH,MYBUL_HEIGHT);
}

void Bullet::bul_recalc(int dir)
{
    if(state == 1){
        if(dir == 0){
            this->y -= p_speed;
        }
        if(dir == 2){
            this->y += e_speed;
        }
    }
    if((this->y+MYBUL_HEIGHT)<=0 || (this->y>=HEIGHT)){
        state = 2;
    }
    bul_rect.setRect(this->x,this->y,MYBUL_WIDTH,MYBUL_HEIGHT);
}

void Bullet::setpix(QPixmap pix)
{
    pix = pix.scaled(MYBUL_WIDTH,MYBUL_HEIGHT , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->bul_pix = pix;
}

void Bullet::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
}
