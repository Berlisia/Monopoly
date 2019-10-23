#pragma once
#include "square.h"

class Penalty : public Square
{
public:
    Penalty(unsigned int p_bonus):
        penaltyPrice(p_bonus)
    {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
private:
    unsigned int penaltyPrice;
};
