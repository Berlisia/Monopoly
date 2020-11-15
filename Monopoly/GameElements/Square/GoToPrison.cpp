#include <iostream>

#include "GoToPrison.h"
#include "Guest.h"

void GoToPrison::actionOnStop(Guest& player)
{
    player.lockInPrison();
}

void GoToPrison::actionOnWalkThrought(Guest&)
{
}

const std::string GoToPrison::squareName()
{
    return GO_TO_PRISON_NAME;
}
