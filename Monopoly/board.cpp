#include "board.h"
#include "square.h"
#include <algorithm>


Board::Board(Squers p_squares): squares(p_squares)
{
}

BoardIterator Board::createBoardIteratorWithStartPossition()
{
    return BoardIterator(squares.begin(), squares.end());
}

