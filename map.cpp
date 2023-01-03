#include "map.h"
#include <QTime>
Map::Map()
{
    maps.push_back(QPixmap(":/map1.jpg"));
    maps.push_back(QPixmap(":/map2.jpg"));
    maps.push_back(QPixmap(":/map3.jpg"));
    maps.push_back(QPixmap(":/map4.jpg"));
    maps.push_back(QPixmap(":/map5.jpg"));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int mapindex = qrand()%5;
    map_1 = maps[mapindex];
    map_2 = maps[mapindex];

    mapy1 = -HEIGHT;
    mapy2 = 0;
    map_speed = 2;
}

void Map::mapposition()
{
    mapy1 += map_speed;
    if(mapy1>=0){
        mapy1 = -HEIGHT;
    }
    mapy2 += map_speed;
    if(mapy2>=HEIGHT){
        mapy2 = 0;
    }
}
