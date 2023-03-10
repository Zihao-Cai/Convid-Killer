#include "plusitem.h"
#include <ctime>
#include "config.h"

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

void Plusitem::move()
{
    //随机移动,随机数决定移动方向
    int dir = rand()%4;
    switch (dir) {
    case 0:y-=6;break;
    case 1:x+=6;break;
    case 2:y+=6;break;
    case 3:x-=6;break;
    }
    this->rect.setRect(x,y,ITEM_SIZE,ITEM_SIZE);
    if(x+ITEM_SIZE<0 || x>WIDTH || y>HEIGHT || y+ITEM_SIZE<0){
        state = 2;
    }
}

void Plusitem::settime(QDateTime time)
{
    this->birth_time = time;
}
