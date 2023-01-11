#ifndef BOMBCARTOON_H
#define BOMBCARTOON_H
#include <QVector>
#include <QPixmap>

class Bombcartoon
{
public:
    Bombcartoon();
    QVector <QPixmap> bombpix;
    int x;
    int y;
    int pix_index;
    int state;
    int interval;

    void setpos(int x,int y);
    void setpix(QPixmap pix);
    void calc();
};

#endif // BOMBCARTOON_H
