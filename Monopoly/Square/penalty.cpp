#include <iostream>

#include "Square/penalty.h"
#include "guest.h"

void Penalty::actionOnStop(Guest& player)
{
    player.withdrawMoney(penaltyPrice); //TODO goTo bancrut if can't pay
}

void Penalty::actionOnWalkThrought(Guest&)
{
}

const std::string Penalty::squareName()
{
    return PENALTY_NAME;
}
