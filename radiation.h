#ifndef RADIATION_H
#define RADIATION_H
#include <QPixmap>
#include <QRect>
#include "config.h"
#include <QDateTime>

class Radiation
{
public:
    Radiation(int par_x,int par_y);
    int x;
    int y;

    QDateTime birth_time;
    QPixmap pix;
    QRect rect;

    void update_pos(int par_x,int par_y);
};

#endif // RADIATION_H
