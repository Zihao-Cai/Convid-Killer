#include "bulpool.h"
#include "config.h"
Bulpool::Bulpool()
{
    for(int i=0;i<BULPOOLSIZE;i++){
        bulpool.push_back(Bullet());
    }
}
