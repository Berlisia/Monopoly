#pragma once
#include "square.h"

class Penalty : public Square
{
public:
    Penalty(unsigned int p_bonus):
        penaltyPrice(p_bonus)
    {}

    void actionOnStop(Player&) override;
    void actionOnWalkThrought(Player&) override;
private:
    unsigned int penaltyPrice;
};
