#pragma once
#include <vector>
#include <memory>
#include "cycliciterator.h"
#include "Square/square.h"

typedef std::vector<std::unique_ptr<Square>> Squers;
typedef CyclicIterator<std::unique_ptr<Square>, Squers::iterator> BoardIterator;

class Board
{
public:
    Board(Squers p_squares);

    BoardIterator createBoardIterator() const;
private:
    Squers squares;
};
