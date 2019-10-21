#include "board.h"
#include <algorithm>


Board::Board(Squers p_squares): squares(std::move(p_squares))
{
}

BoardIterator Board::createBoardIterator()
{
    return BoardIterator(squares.begin(), squares.end());
}

