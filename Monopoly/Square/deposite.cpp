#include "deposite.h"
#include "guest.h"

#include <iostream>

void Deposite::actionOnStop(Guest& player)
{
    player.addMoney(depositeMoney);
    std::cout << "  Stop on DEPOSITE get money: " << depositeMoney << std::endl;
    depositeMoney = 0;
}

void Deposite::actionOnWalkThrought(Guest& player)
{
    player.withdrawMoney(valueToStore);
    depositeMoney += valueToStore;
    std::cout << "  Walk throught DEPOSITE money  in deposite: " << depositeMoney << std::endl;
}
