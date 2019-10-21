#include "blackhole.h"

void BlackHole::actionOnStop(Player &)
{
    if(isActive)
    {
        isActive = false;
    }
    else
    {

    }
}

void BlackHole::actionOnWalkThrought(Player &)
{

}
