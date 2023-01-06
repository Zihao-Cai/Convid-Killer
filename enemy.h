#ifndef ENEMY_H
#define ENEMY_H
#include "config.h"
#include "bullet.h"

class Enemy
{
public:
    Enemy();
    int x;
    int y;
    int dir;
    int state;
    int shot_intv;
    int islive;
    QPixmap pix_plane;
    QRect rect;
    QVector <Bullet> enbuls;
    void setpos(int x,int y);
    void setpix(QPixmap pix);
    void shoot(int flag);
    void move(int tempdir);

};

#endif // ENEMY_H
