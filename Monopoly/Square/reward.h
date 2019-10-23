#pragma once
#include "square.h"
class Reward : public Square
{
public:
    Reward(int p_bonus):
        bonus(p_bonus)
    {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
private:
    unsigned int bonus;
};
