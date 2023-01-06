#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include <QRect>
#include "config.h"
#include "bullet.h"

class Plane
{
public:
    Plane(Bulpool* pool);
    int x;
    int y;
    int dir;
    int islive;
    QPixmap pix_plane;
    QRect rect;
    QVector <Bullet> mybuls;
    Bulpool* pool;
    void setpos(int x,int y);
    void setpix(QPixmap pix);
    void shoot();
    void move(int dir);
};

#endif // PLANE_H
