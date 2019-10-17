#include "deposite.h"

unsigned int Deposite::depositeMoney = 0;

void Deposite::actionOnStop(Player& player) const
{
    player.setNewResult(player.getActualResult() + depositeMoney);
    depositeMoney = 0;
}

void Deposite::actionOnWalkThrought(Player& player) const
{
    player.withdrawMoney(valueToStore);
    depositeMoney += valueToStore;
}
