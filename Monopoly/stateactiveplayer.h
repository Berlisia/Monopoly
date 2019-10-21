#pragma once
#include "state.h"
#include "player.h"

class StateActivePlayer: public State
{
public:
    void turn(Player& player) override;

};

void StateActivePlayer::turn(Player& player)
{
    auto valueOfSteps = player.throwDice();
    player.moveOn(valueOfSteps);
}
