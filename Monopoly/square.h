#pragma once
#include "player.h"

class Square
{
public:
    virtual ~Square() {}

    virtual void actionOnStop(Player&) const = 0;
    virtual void actionOnWalkThrought(Player&) const = 0;

};

