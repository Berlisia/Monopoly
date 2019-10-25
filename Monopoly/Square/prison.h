#pragma once

#include "square.h"

class Prison: public Square
{
public:
    virtual void actionOnStop(Guest&);
    virtual void actionOnWalkThrought(Guest&);
};
