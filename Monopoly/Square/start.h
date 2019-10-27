#pragma once
#include "Square/square.h"

const std::string START_NAME = "START";

class Start : public Square
{
public:
    Start(unsigned int p_bonus):
        bonus(p_bonus) {}

    void actionOnStop(Guest& player) override;
    void actionOnWalkThrought(Guest& player) override;
    const std::string squareName() override;

private:
    const unsigned int bonus;
};
