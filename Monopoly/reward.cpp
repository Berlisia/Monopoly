#include "reward.h"
#include <iostream>

#include "player.h"

void Reward::actionOnStop(Player& player)
{
    player.setNewResult(player.getActualResult() + bonus);
    std::cout << "Stop on REWARD + " <<  bonus << std::endl;
}

void Reward::actionOnWalkThrought(Player &)
{
    std::cout << "Walk throught REWARD" << std::endl;
}
