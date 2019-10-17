#pragma once
#include "square.h"
class Reward : public Square
{
public:
    Reward(int p_bonus):
        bonus(p_bonus)
    {}

    void actionOnStop(Player&) override;
    void actionOnWalkThrought(Player&) override;
private:
    int bonus;
};
