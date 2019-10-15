#include "reward.h"
#include <iostream>

int Reward::action() const
{
    std::cout << "Reward " << std::endl;
    return bonus;
}

unsigned int Reward::getPossition() const
{
    return possition;
}
