#ifndef ENTITY
#define ENTITY

#include "Entity.h"
#include <iostream>

class Entity{
public :
    int getTimer();
    void setTimer(int time);
    int getPv();
    void setPv(int _pv);
private :
    int timer;
    int pv;
    int arme;
    int speed;
    
};

#endif