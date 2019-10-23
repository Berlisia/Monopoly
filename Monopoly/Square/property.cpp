#include <iostream>

#include "property.h"
#include "player.h"

void Property::actionOnStop(Guest& player)
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

void Property::actionOnWalkThrought(Guest&)
{
}

void Property::payRentByGuest(Guest& player)
{
    if(!owner->myName().compare(player.myName()))
    {
        auto money = player.withdrawMoney(rent);
        owner->addMoney(money);
        std::cout << player.myName() << " buy rent for " << owner->myName() << std::endl;
    }
}

void Property::buyPropertyByNewOwner(Guest& player)
{
    if(player.wantBuyProperty(price))
    {
        player.withdrawMoney(price);
        owner = &player;
        std::cout << " New owner " << owner->myName() << std::endl;
    }
}
