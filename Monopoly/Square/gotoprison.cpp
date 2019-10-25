#include <iostream>

#include "gotoprison.h"
#include "guest.h"

void GoToPrison::actionOnStop(Guest& player)
{
    player.lockInPrison(prisonPossisionOnBoard);
    std::cout<< " Stop on GO TO PRISON" << std::endl;
}

void GoToPrison::actionOnWalkThrought(Guest &)
{
}
