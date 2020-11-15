#pragma once
#include <memory>
#include <vector>

#include "CyclicIterator.h"
#include "Square.h"

typedef std::vector<std::unique_ptr<Square>> Squers;
typedef CyclicIterator<std::unique_ptr<Square>, Squers::iterator> BoardIterator;

class Board {
public:
  Board(Squers p_squares);

  BoardIterator createBoardIterator();

private:
  Squers squares;
};
