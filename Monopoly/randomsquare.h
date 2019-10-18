#pragma once
#include "square.h"
#include "board.h"

class RandomSquare: public Square
{
public:
    RandomSquare(Squers p_squares):  squares(std::move(p_squares)){}

    virtual void actionOnStop(Player&);
    virtual void actionOnWalkThrought(Player&);

private:
    Squers squares;

    unsigned int randomNumber();
};
