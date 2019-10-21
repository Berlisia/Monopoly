#pragma once
#include "square.h"
#include <memory>

class BlackHole: public Square
{
public:
    virtual void actionOnStop(Player&);
    virtual void actionOnWalkThrought(Player&);

private:
    bool isActive = false;
    std::unique_ptr<Square> square;

};
