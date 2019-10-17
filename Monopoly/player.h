#pragma once
#include <string>

#include "die.h"
#include "board.h"

class Player
{
public:
    Player(std::string p_name, const Dice & p_dice, BoardIterator p_boardIterator):
        name(p_name),
        dice(p_dice),
        actualPossisionOnBoard(p_boardIterator)
    {}

    std::vector<Square*> turn();
    void setNewResult(int newResult);
    int getActualResult();
    void withdrawMoney(unsigned int money);
    void printStatus();

private:
    std::string name;
    const Dice & dice;
    BoardIterator actualPossisionOnBoard;
    int result = 0;

    unsigned int throwDice();
    std::vector<Square*> move(unsigned int valueOfSteps);

};
