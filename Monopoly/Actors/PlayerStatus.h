#pragma once

#include "Board.h"

class Estate;

class PlayerStatus {
public:
  PlayerStatus(const BoardIterator &possition, unsigned int money,
               const std::vector<const Estate *> &props)
      : actualPossisionOnBoard(possition), moneyInWalet(money),
        propertis(props) {}

  void update();

  const std::string possition();
  unsigned int money();
  const std::vector<const Estate *> havePropertis();

private:
  BoardIterator actualPossisionOnBoard;
  unsigned int moneyInWalet;
  std::vector<const Estate *> propertis;

  void printPropertis();
};
