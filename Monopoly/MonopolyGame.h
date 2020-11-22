#pragma once
#include "Bank.h"
#include "Board.h"
#include "Contestant.h"
#include "Die.h"

using Players = std::map<std::unique_ptr<Contestant>, BoardIterator>;
using PlayerWithPossiton = std::pair<std::unique_ptr<Contestant>, BoardIterator>;

class MonopolyGame
{
public:
    MonopolyGame(Board p_board, Players p_players) : board(std::move(p_board)), players(std::move(p_players)), bank() {}

    void startGame(unsigned int numberOfTurns);

private:
    Board board;
    Players players;
    Bank bank;

    Square* actualSquare(BoardIterator& possition);
    void walkThrought(Contestant& player, BoardIterator& possition);
    void actionOnStop(Contestant& player, BoardIterator& possition);
};
