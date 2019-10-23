#pragma once
#include "square.h"
#include "board.h"

class RandomSquare: public Square
{
public:
    RandomSquare(Squers p_squares):  squares(std::move(p_squares)){}

    virtual void actionOnStop(Guest&);
    virtual void actionOnWalkThrought(Guest&);

private:
    Squers squares;

    unsigned int randomNumber();
};
