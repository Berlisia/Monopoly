#pragma once
#include <string>

#include "die.h"
#include "board.h"

class Player
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator):
        name(p_name),
        actualPossisionOnBoard(p_boardIterator)
    {}

    Square* moveNextSquare();
    unsigned int throwDice();

    void setNewResult(int newResult);
    int getActualResult();
    unsigned int withdrawMoney(unsigned int money);
    void printStatus();
    bool comparePlayer(const Player& player);
    bool wantBuyProperty(unsigned int price);
    unsigned int lockInPrison(unsigned int numberfOfTurns);
    bool isInPrison();

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    Dice dice;

    unsigned int numberOfSkipedTurns = 0;
    int result = 0;
    bool isBancrut = false;

};
