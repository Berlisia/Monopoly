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

    void actionOnStop(Player& player) const override;
    void actionOnWalkThrought(Player& player) const override;
private:
    int bonus;
};
