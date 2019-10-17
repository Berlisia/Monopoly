#pragma once
#include "board.h"
#include <memory>
#include "cycliciterator.h"

class Piece
{
public:
    Piece(BoardIterator p_boardIterator): actualPossisionOnBoard(p_boardIterator)
    {
    }

    Squers move(int valueOfSteps);
private:
    BoardIterator actualPossisionOnBoard;
};
