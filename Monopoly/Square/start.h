#pragma once
#include "Square/square.h"

class Start : public Square
{
public:
    Start(int p_bonus):
        bonus(p_bonus)
    {
    }

    void actionOnStop(Guest& player) override;
    void actionOnWalkThrought(Guest& player) override;
private:
    unsigned int bonus;
};
