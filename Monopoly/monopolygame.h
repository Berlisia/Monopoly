#pragma once
#include "board.h";
#include "die.h"

class MonopolyGame
{
public:
    MonopolyGame(Board p_board, Dice p_dice):
        board(p_board),
        dice(p_dice) {}

    void startGame();
private:
    Board board;
    Dice dice;
};
