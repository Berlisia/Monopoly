#pragma once
#include "square.h"

const std::string PENALTY_NAME = "PENALTY";

class Penalty : public Square
{
public:
    Penalty(const unsigned int p_bonus):
        penaltyPrice(p_bonus) {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

private:
    const unsigned int penaltyPrice;
};
