#pragma once

#include "board.h"
#include "printer.h"

class Estate;

class PlayerStatus : public Printer
{
public:
    PlayerStatus(const BoardIterator& possition, unsigned int money, const std::vector<const Estate*>& props):
         actualPossisionOnBoard(possition),
         moneyInWalet(money),
         propertis(props){}

    void update() override;

    const std::string possition();
    unsigned int money();
    const std::vector<const Estate*> havePropertis();

private:
    BoardIterator actualPossisionOnBoard;
    unsigned int moneyInWalet;
    std::vector<const Estate*> propertis;

    void printPropertis();
};
