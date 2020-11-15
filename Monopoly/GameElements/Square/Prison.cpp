#include <iostream>

#include "Guest.h"
#include "Prison.h"

void Prison::actionOnStop(Guest&)
{
}

void Prison::actionOnWalkThrought(Guest&)
{
}

const std::string Prison::squareName()
{
    return PRISON_NAME;
}
