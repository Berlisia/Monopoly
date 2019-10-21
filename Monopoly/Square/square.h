#pragma once

class Player;

class Square
{
public:
    virtual ~Square() = default;

    virtual void actionOnStop(Player&) = 0;
    virtual void actionOnWalkThrought(Player&) = 0;

protected:
    bool isBlackHole = false;

};

