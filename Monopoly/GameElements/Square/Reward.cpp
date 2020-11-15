#include "Reward.h"
#include "Guest.h"

#include <iostream>

void Reward::actionOnStop(Guest& player)
{
    player.addMoney(bonus);
}

void Reward::actionOnWalkThrought(Guest&)
{
}

const std::string Reward::squareName()
{
    return REWARD_NAME;
}
