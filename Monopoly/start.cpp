#include "start.h"
#include <iostream>

void Start::actionOnStop(Player& player)
{
    player.setNewResult(player.getActualResult() + bonus);
    std::cout << "  Stop on START + " <<  bonus << std::endl;
}

void Start::actionOnWalkThrought(Player& player)
{
    player.setNewResult(player.getActualResult() + bonus);
    std::cout << "  Walk throught START + " <<  bonus << std::endl;
}
