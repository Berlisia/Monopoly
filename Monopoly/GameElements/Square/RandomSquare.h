#pragma once
#include "Board.h"

const std::string RANDOM_SQUARE_NAME = "RANDOM SQUARE";

class RandomSquare : public Square {
public:
  RandomSquare(Squers p_squares) : squares(std::move(p_squares)) {}

  void actionOnStop(Guest &) override;
  void actionOnWalkThrought(Guest &) override;
  const std::string squareName() override;

private:
  Squers squares;

  unsigned int randomNumber();
};
