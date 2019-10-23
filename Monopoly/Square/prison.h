#pragma once

#include "square.h"

class Prisone: public Square
{
public:
    virtual void actionOnStop(Guest&);
    virtual void actionOnWalkThrought(Guest&);
};
