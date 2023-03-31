#include "boss.h"

#include <QTime>
Boss::Boss()
{
    blood = 50;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    x = qrand()%WIDTH-BOSS_WIDTH;
    y = -BOSS_HEIGHT;
    setpix(QPixmap(":/boos.jpg"));
}

bool Boss::setpix(QPixmap)
{

}
