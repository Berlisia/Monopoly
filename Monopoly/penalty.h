#pragma once
#include "square.h"

class Penalty : public Square
{
public:
    Penalty(int p_bonus):
        bonus(p_bonus)
    {}

    void actionOnStop(Player&) override;
    void actionOnWalkThrought(Player&) override;
private:
    int bonus;
};
