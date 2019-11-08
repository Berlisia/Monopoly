#include <iostream>

#include "property.h"
#include "player.h"

void Property::actionOnStop(Guest& player)
{
    if(owner)
    {
        if(not (owner->myName() == player.myName()))
        {
            payRentMode->payRent(player, *owner);
        }
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

const std::string& Property::estateName() const
{
    return name;
}

void Property::buyPropertyByNewOwner(Guest& player)
{
    if(player.buyProperty(price, this, district))
    {
        owner = &player;
    }
}
