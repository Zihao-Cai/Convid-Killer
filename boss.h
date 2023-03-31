#ifndef BOSS_H
#define BOSS_H
#include <QPixmap>
#include "config.h"

class Boss
{
public:
    Boss();
    int x;
    int y;
    int dir;
    int speed;
    int blood;
    QPixmap boss_pix;
    QRect rect;
    void move(int tempdir);
    bool setpos(int x, int y);
    bool setpix(QPixmap);
};

#endif // BOSS_H
