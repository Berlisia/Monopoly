#include <iostream>

#include "gotoprison.h"
#include "guest.h"

void GoToPrison::actionOnStop(Guest& player)
{
    player.lockInPrison(prisonPossisionOnBoard);
}

void GoToPrison::actionOnWalkThrought(Guest &)
{
}

const std::string GoToPrison::squareName()
{
    return GO_TO_PRISON_NAME;
}
