#pragma once
#include "Bank.h"
#include "Board.h"
#include "Contestant.h"
#include "Die.h"

typedef std::vector<std::unique_ptr<Contestant>> Players;

class MonopolyGame {
public:
  MonopolyGame(Board p_board, Players p_players)
      : board(std::move(p_board)), players(std::move(p_players)), bank() {}

  void startGame(unsigned int numberOfTurns);

private:
  Board board;
  Players players;
  Bank bank;

  void turn(Contestant &player);
};
