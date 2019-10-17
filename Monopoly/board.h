#pragma once
#include <vector>
#include <memory>
#include "cycliciterator.h"
#include "square.h"

typedef std::vector<std::unique_ptr<Square>> Squers;
typedef CyclicIterator<std::unique_ptr<Square>, Squers::iterator> BoardIterator;

class Board
{
public:
    Board(Squers p_squares);

    BoardIterator createBoardIterator();
private:
    Squers squares;
    const int numberOfSquares = 40;
};
