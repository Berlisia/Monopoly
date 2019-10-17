#pragma once
#include <vector>
#include <memory>
#include "cycliciterator.h"

class Square;
typedef std::vector<std::shared_ptr<Square>> Squers;
typedef CyclicIterator<std::shared_ptr<Square>, Squers::iterator> BoardIterator;

class Board
{
public:
    Board(Squers p_squares);

    BoardIterator createBoardIteratorWithStartPossition();
private:
    Squers squares;
    const int numberOfSquares = 40;
};
