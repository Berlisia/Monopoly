#pragma once

#include "square.h"
#include "board.h"

class GoToPrison: public Square
{
public:
    GoToPrison(BoardIterator p_prisonOnBoard):
        prisonPossisionOnBoard(p_prisonOnBoard){}

    virtual void actionOnStop(Guest&);
    virtual void actionOnWalkThrought(Guest&);

private:
    Squers::iterator prisonPossisionOnBoard;
};

