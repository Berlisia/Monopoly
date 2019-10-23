#pragma once
#include "square.h"
#include <memory>

class BlackHole: public Square
{
public:
    virtual void actionOnStop(Guest&);
    virtual void actionOnWalkThrought(Guest&);

private:
    bool isActive = false;
    std::unique_ptr<Square> square;

};
