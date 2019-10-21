#pragma once

#include "square.h"

class Prisone: public Square
{
public:
    virtual void actionOnStop(Player&);
    virtual void actionOnWalkThrought(Player&);
};
