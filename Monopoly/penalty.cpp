#include "penalty.h"
#include <iostream>

#include "player.h"

void Penalty::actionOnStop(Player& player)
{
    player.setNewResult(player.getActualResult() - bonus);
    std::cout << "  Stop on penalty - " << bonus << std::endl;
}

void Penalty::actionOnWalkThrought(Player&)
{
    std::cout << "  Walk throught penalty" << std::endl;
}
