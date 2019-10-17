#include "reward.h"
#include <iostream>

void Reward::actionOnStop(Player& player) const
{
    player.setNewResult(player.getActualResult() + bonus);
}

void Reward::actionOnWalkThrought(Player &) const
{

}
