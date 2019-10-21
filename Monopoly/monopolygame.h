#pragma once
#include "board.h"
#include "die.h"

class MonopolyGame
{
public:
    MonopolyGame(Board p_board):
        board(std::move(p_board)) {}

    void startGame(unsigned int numberOfTurns);
private:
    Board board;

    void turn(Player& player);
};
