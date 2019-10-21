#include "property.h"
#include "player.h"

void Property::actionOnStop(Player& player)
{
    std::cout << " stop on PROPERTY ";
    if(owner)
    {
        payRentByGuest(player);
    }
    else
    {
        buyPropertyByNewOwner(player);
    }
}

void Property::actionOnWalkThrought(Player &)
{
}

void Property::payRentByGuest(Player& player)
{
    if(!owner->comparePlayer(player))
    {
        auto money = player.withdrawMoney(rent);
        owner->addMoney(money);
        std::cout << player.myName() << " buy rent for " << owner->myName() << std::endl;
    }
}

void Property::buyPropertyByNewOwner(Player& player)
{
    if(player.wantBuyProperty(price))
    {
        player.withdrawMoney(price);
        owner = &player;
        std::cout << " New owner " << owner->myName() << std::endl;
    }
}
