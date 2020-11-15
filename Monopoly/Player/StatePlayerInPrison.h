#pragma once
#include "Player.h"
#include "State.h"
#include "StateActivePlayer.h"

class StatePlayerInPrison : public State
{
public:
    void turn(Player& player) override;

private:
    unsigned int numberOfSkipedTurns = 2;
};

void StatePlayerInPrison::turn(Player& player)
{
    numberOfSkipedTurns--;
    if (numberOfSkipedTurns == 0)
    {
        player.stateTransition(std::make_unique<StateActivePlayer>());
    }
}
