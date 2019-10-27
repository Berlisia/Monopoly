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
    player.withdrawMoney(valueToStore);
    depositeMoney += valueToStore;
}

const std::string Deposite::squareName()
{
    return DEPOSITE_NAME;
}
