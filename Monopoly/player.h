#pragma once
#include <string>
#include "piece.h"
#include "die.h"
#include <iostream>

class Player
{
public:
    Player(std::string p_name, Piece p_piece, const Dice & p_dice):
        name(p_name),
        piece(p_piece),
        dice(p_dice)
    {}

    void turn();
    void setNewResult(int newResult);
    const int getActualResult();
    void withdrawMoney(unsigned int money);

private:
    std::string name;
    Piece piece;
    const Dice & dice;
    int result = 0;

    int throwDice();
};
