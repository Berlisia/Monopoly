#include <iostream>

#include "Square/penalty.h"
#include "guest.h"

void Penalty::actionOnStop(Guest& player)
{
    player.withdrawMoney(penaltyPrice);
    std::cout << "  Stop on penalty - " << penaltyPrice << std::endl;
}

void Penalty::actionOnWalkThrought(Guest&)
{
}
