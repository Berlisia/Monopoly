#include "reward.h"
#include "guest.h"

#include <iostream>


void Reward::actionOnStop(Guest& player)
{
    player.addMoney(bonus);
    std::cout << "  Stop on REWARD + " <<  bonus << std::endl;
}

void Reward::actionOnWalkThrought(Guest &)
{
}
