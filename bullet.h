#ifndef BULLET_H
#define BULLET_H
#include <QPixmap>
#include <QRect>

class Bullet
{
public:
    Bullet(int par_x,int par_y,int dir,bool up);
    Bullet();
    int x;
    int y;
    QPixmap bul_pix;
    QRect bul_rect;
    int p_speed;
    int e_speed;
    int state;
    bool isup = false;

    void bul_recalc(int dir);
    void setpix(QPixmap pix);
    void setpos(int x,int y);

};

#endif // BULLET_H
