#include <iostream>

#include "Estate.h"
#include "PlayerStatus.h"

void PlayerStatus::update()
{
    std::cout << "  Stop on: " << (*actualPossisionOnBoard).get()->squareName() << std::endl;
    std::cout << "  Money in walet: " << moneyInWalet << std::endl;
    printPropertis();
}

const std::string PlayerStatus::possition()
{
    return (*actualPossisionOnBoard).get()->squareName();
}

unsigned int PlayerStatus::money()
{
    return moneyInWalet;
}

const std::vector<const Estate*> PlayerStatus::havePropertis()
{
    return propertis;
}

void PlayerStatus::printPropertis()
{
    std::cout << "  Have propertis: " << std::endl;
    std::cout << "  ";
    for (auto prop : propertis)
    {
        std::cout << prop->estateName() << " | ";
    }
    std::cout << std::endl;
}
