#pragma once

class Square;
class Player;

class State
{
public:
    virtual ~State() = default;

    virtual void turn(Player&) = 0;
};
