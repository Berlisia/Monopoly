#pragma once
#include "square.h"

const std::string REWARD_NAME = "REWARD";

class Reward : public Square
{
public:
    Reward(const unsigned int p_bonus):
        bonus(p_bonus) {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

private:
    const unsigned int bonus;
};
