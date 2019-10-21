#include "reward.h"
#include <iostream>

#include "player.h"

void Reward::actionOnStop(Player& player)
{
    player.addMoney(bonus);
    std::cout << "  Stop on REWARD + " <<  bonus << std::endl;
}

void Reward::actionOnWalkThrought(Player &)
{
}
