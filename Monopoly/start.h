#pragma once
#include "square.h"
#include <functional>
#include "player.h"

class Start : public Square
{
public:
    Start(int p_bonus):
        bonus(p_bonus)
    {
    }

    void actionOnStop(Player& player) override;
    void actionOnWalkThrought(Player& player) override;
private:
    unsigned int bonus;
};
