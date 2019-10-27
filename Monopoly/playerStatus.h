#pragma once

#include "board.h"
#include "printer.h"

class Property;

class PlayerStatus : public Printer
{
public:
    PlayerStatus(const BoardIterator& possition, unsigned int money, const std::vector<Property*>& props):
         actualPossisionOnBoard(possition),
         moneyInWalet(money),
         propertis(props){}

    void update() override;

    const std::string possition();
    unsigned int money();
    const std::vector<Property*> havePropertis();

private:
    BoardIterator actualPossisionOnBoard;
    unsigned int moneyInWalet;
    std::vector<Property*> propertis;

    void printPropertis();
};
