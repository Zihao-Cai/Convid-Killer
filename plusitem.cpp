#include "plusitem.h"
#include <ctime>

Plusitem::Plusitem()
{
    srand((unsigned int) time(NULL));
    //加成道具在地图内随机位置出现
    setpos(rand()%(WIDTH-ITEM_SIZE+1),rand()%(HEIGHT-ITEM_SIZE+1));
    int flag = rand()%3;
    if(flag == 0){
        setpix(QPixmap(":/blood.png"));
        type = ITEM_BLOOD;
    }else {
        setpix(QPixmap(":/upgrade.png"));
        type = ITEM_UPGRADE;
    }
    state = 0;
}

void Plusitem::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
    this->rect.setRect(x,y,ITEM_SIZE,ITEM_SIZE);
}

void Plusitem::setpix(QPixmap itempix)
{
    itempix = itempix.scaled(ITEM_SIZE,ITEM_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pix = itempix;
}
