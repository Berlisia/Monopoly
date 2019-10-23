#include <iostream>

#include "prison.h"
#include "guest.h"

void Prisone::actionOnStop(Guest& player)
{
    player.lockInPrison();
    std::cout<< " Stop on PRISON" << std::endl;
}

void Prisone::actionOnWalkThrought(Guest &)
{
}
