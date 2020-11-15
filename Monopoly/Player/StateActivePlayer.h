#pragma once
#include "Player.h"
#include "State.h"

class StateActivePlayer : public State
{
public:
    void turn(Player& player) override;
};

void StateActivePlayer::turn(Player& player)
{
    player.move();
}
