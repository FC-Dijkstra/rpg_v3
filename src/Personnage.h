#ifndef PERSONNAGE
#define PERSONNAGE
#include "Entity.h"
#include <iostream>

class Personnage : public Entity {
    public:
        Personnage(int pv);
};

#endif