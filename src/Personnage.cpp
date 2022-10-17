#include "Entity.h"
#include "Personnage.h"
#include <iostream>

Personnage::Personnage(int pv)
{
    setPv(pv);
    setTimer(0);
}
