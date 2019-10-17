#include "deposite.h"
#include "player.h"

void Deposite::actionOnStop(Player& player)
{
    player.setNewResult(player.getActualResult() + depositeMoney);
    depositeMoney = 0;
}

void Deposite::actionOnWalkThrought(Player& player)
{
    player.withdrawMoney(valueToStore);
    depositeMoney += valueToStore;
}
