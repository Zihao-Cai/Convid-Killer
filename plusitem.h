#ifndef PLUSITEM_H
#define PLUSITEM_H
#include <QPixmap>
#include <QRect>
#include "config.h"
#include <QDateTime>

class Plusitem
{
public:
    Plusitem();
    int x;
    int y;
    int state;
    int type;
    QPixmap pix;
    QRect rect;
    QDateTime birth_time;

    void setpos(int x,int y);
    void setpix(QPixmap itempix);
    void move();
    void settime(QDateTime time);

};

#endif // PLUSITEM_H
