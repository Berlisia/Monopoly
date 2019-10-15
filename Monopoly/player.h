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
        dice(p_dice){}

    void turn()
    {
        const Square& square = piece.move(throwDice());

        result += square.action();
        std::cout << name << ": " << result << endl;
    }

private:
    std::string name;
    Piece piece;
    const Dice & dice;
    int result = 0;
    int deposite = 0;

    int throwDice()
    {
        return dice.diceThrow();
    }
};
