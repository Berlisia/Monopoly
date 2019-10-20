#include "deposite.h"
#include "player.h"

void Deposite::actionOnStop(Player& player)
{
    player.addMoney(depositeMoney);
    std::cout << "  Stop on DEPOSITE get money: " << depositeMoney << std::endl;
    depositeMoney = 0;
}

void Deposite::actionOnWalkThrought(Player& player)
{
    player.withdrawMoney(valueToStore);
    depositeMoney += valueToStore;
    std::cout << "  Walk throught DEPOSITE money  in deposite: " << depositeMoney << std::endl;
}
