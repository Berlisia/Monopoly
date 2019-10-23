#pragma once

class Guest;

class Square
{
public:
    virtual ~Square() = default;

    virtual void actionOnStop(Guest&) = 0;
    virtual void actionOnWalkThrought(Guest&) = 0;

};

