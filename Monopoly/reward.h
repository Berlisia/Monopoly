#pragma once
#include "square.h"
class Reward : public Square
{
public:
    Reward(int p_bonus):
        bonus(p_bonus)
    {}

    void actionOnStop(Player&) const override;
    void actionOnWalkThrought(Player&) const override;
private:
    int bonus;
};
