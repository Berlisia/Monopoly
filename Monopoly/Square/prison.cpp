#include <iostream>

#include "prison.h"
#include "guest.h"

void Prison::actionOnStop(Guest&)
{
}

void Prison::actionOnWalkThrought(Guest &)
{
}

const std::string Prison::squareName()
{
    return PRISON_NAME;
}
