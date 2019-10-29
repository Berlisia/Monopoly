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

const std::string& Property::estateName()
{
    return name;
}

void Property::payRentByGuest(Guest& player)
{
    if(not (owner->myName() == player.myName()))
    {
        auto ownerHavePropertis = owner->checkPropertisInDistrict(district.propertis());
        auto money = player.withdrawMoney(rent.at(ownerHavePropertis));
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
