#include <iostream>

#include "prison.h"
#include "guest.h"

void Prison::actionOnStop(Guest& player)
{
    std::cout<< " Stop on PRISON" << std::endl;
}

void Prison::actionOnWalkThrought(Guest &)
{
}
