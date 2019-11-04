#include "deposite.h"
#include "guest.h"

#include <iostream>

void Deposite::actionOnStop(Guest& player)
{
    player.addMoney(depositeMoney);
    depositeMoney = 0;
}

void Deposite::actionOnWalkThrought(Guest& player)
{
    if(player.withdrawMoney(valueToStore))//TODO goTo bancrut if can't pay.
    {
        depositeMoney += valueToStore;
    }
}

const std::string Deposite::squareName()
{
    return DEPOSITE_NAME;
}
