#include "penalty.h"
#include <iostream>

#include "player.h"

void Penalty::actionOnStop(Player& player)
{
    player.withdrawMoney(penaltyPrice);
    std::cout << "  Stop on penalty - " << penaltyPrice << std::endl;
}

void Penalty::actionOnWalkThrought(Player&)
{
}
