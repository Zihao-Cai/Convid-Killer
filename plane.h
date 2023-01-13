#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include <QRect>
#include "config.h"
#include "bullet.h"

class Plane
{
public:
    Plane();
    int x;
    int y;
    int dir;
    int tempdir;
    int state;
    int blood;
    bool isup;
    QPixmap pix_plane;
    QRect rect;
    QVector <Bullet> mybuls;
    void setpos(int x,int y);
    void setpix(QPixmap pix);
    void shoot(bool up);
    void move(int dir);
};

#endif // PLANE_H
