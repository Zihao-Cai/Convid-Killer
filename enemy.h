#ifndef ENEMY_H
#define ENEMY_H
#include "config.h"
#include "bullet.h"
#include "radiation.h"

class Enemy
{
public:
    Enemy();
    int x;
    int y;
    int dir;
    int speed;
    int state;
    int blood;
    bool isbingdu;
    QPixmap pix_plane;
    QRect rect;
    QVector <Bullet> enbuls;
    Radiation* en_radi;
    QDateTime radi_time;
    QDateTime last_shoot;
    QDateTime last_radi;
    bool radi_flag = false;
    bool radi_open = false;
    bool setradi = true;
    void setpos(int x,int y);
    void setpix(QPixmap pix);
    void shoot(int flag);
    bool radi_shoot();
    void move(int tempdir);

};

#endif // ENEMY_H
