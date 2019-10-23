#include "start.h"
#include "guest.h"

#include <iostream>

void Start::actionOnStop(Guest& player)
{
    player.addMoney(bonus);
    std::cout << "  Stop on START + " <<  bonus << std::endl;
}

void Start::actionOnWalkThrought(Guest& player)
{
    player.addMoney(bonus);
    std::cout << "  Walk throught START + " <<  bonus << std::endl;
}
