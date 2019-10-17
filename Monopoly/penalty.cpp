#include "penalty.h"
#include <iostream>

void Penalty::actionOnStop(Player& player) const
{
    player.setNewResult(player.getActualResult() - bonus);
}

void Penalty::actionOnWalkThrought(Player& player) const
{

}
