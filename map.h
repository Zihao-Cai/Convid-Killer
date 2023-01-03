#ifndef MAP_H
#define MAP_H
#include "config.h"

class Map
{
public:
    Map();
    QVector<QPixmap> maps;
    QPixmap map_1;
    QPixmap map_2;
    int mapy1,mapy2;
    int map_speed;
    void mapposition();

};

#endif // MAP_H
