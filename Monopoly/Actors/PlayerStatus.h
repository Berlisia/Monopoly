#pragma once

#include "Board.h"

class Estate;

class PlayerStatus
{
public:
    PlayerStatus(unsigned int money, const std::vector<const Estate*>& props) : moneyInWalet(money), propertis(props) {}

    void update(const BoardIterator& possition);
    unsigned int money();
    const std::vector<const Estate*> havePropertis();

private:
    unsigned int moneyInWalet;
    std::vector<const Estate*> propertis;

    void printPropertis();
    const std::string possition(const BoardIterator& possition);
};
