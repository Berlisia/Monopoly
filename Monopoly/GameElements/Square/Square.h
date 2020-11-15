#pragma once
#include <string>

class Guest;

class Square
{
public:
    virtual ~Square() = default;

    virtual void actionOnStop(Guest&) = 0;
    virtual void actionOnWalkThrought(Guest&) = 0;
    virtual const std::string squareName() = 0; // TODO Remove from this
};
