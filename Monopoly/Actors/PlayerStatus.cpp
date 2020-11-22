#include <iostream>

#include "Estate.h"
#include "PlayerStatus.h"

void PlayerStatus::update(const BoardIterator& possitionOnBoard)
{
    std::cout << "  Stop on: " << possition(possitionOnBoard) << std::endl;
    std::cout << "  Money in walet: " << moneyInWalet << std::endl;
    printPropertis();
}

const std::string PlayerStatus::possition(const BoardIterator& possition)
{
    return (*possition).get()->squareName();
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
