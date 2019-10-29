#include <iostream>

#include "property.h"
#include "player.h"

void Property::actionOnStop(Guest& player)
{
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

const std::string Property::squareName()
{
    return name;
}

bool Property::operator ==(const Property &prop) const
{
    return name.compare(prop.name) &&
           price == prop.price;
}

void Property::payRentByGuest(Guest& player)
{
    if(!owner->myName().compare(player.myName()))
    {
        auto money = player.withdrawMoney(rent.at(1));
        owner->addMoney(money);
    }
}

void Property::buyPropertyByNewOwner(Guest& player)
{
    if(player.buyProperty(price, this))
    {
        owner = &player;
    }
}
