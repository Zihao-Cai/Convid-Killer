#ifndef PLUSITEM_H
#define PLUSITEM_H
#include <QPixmap>
#include <QRect>
#include "config.h"

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

    void setpos(int x,int y);
    void setpix(QPixmap itempix);
};

#endif // PLUSITEM_H
