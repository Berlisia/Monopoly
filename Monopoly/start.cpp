#include "start.h"
#include <iostream>

void Start::actionOnStop(Player& player) const
{
    player.setNewResult(player.getActualResult() + bonus);
}

void Start::actionOnWalkThrought(Player& player) const
{
    player.setNewResult(player.getActualResult() + bonus);
}
