#pragma once
#include "Player.h"
#include "State.h"

class StatePlayerBancrut : public State
{
public:
    void turn(Player& player) override;
};

void StatePlayerBancrut::turn(Player& player)
{
    std::cout << player.myName() << " is BUNCRUT" << std::endl;
}
