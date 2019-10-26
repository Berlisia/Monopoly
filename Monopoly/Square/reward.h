#pragma once
#include "square.h"
class Reward : public Square
{
public:
    Reward(const unsigned int p_bonus):
        bonus(p_bonus)
    {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
private:
    const unsigned int bonus;
};
