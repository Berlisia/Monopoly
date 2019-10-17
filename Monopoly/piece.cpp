#include "piece.h"
#include <functional>
#include <iostream>

Squers Piece::move(int valueOfSteps)
{
    Squers visitSquares;
    for(auto i = 0; i < valueOfSteps; i++)
    {
        ++actualPossisionOnBoard;
        visitSquares.push_back(*actualPossisionOnBoard);
    }
    return visitSquares;
}

