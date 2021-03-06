#include <iostream>

#include "Guest.h"
#include "Property.h"

void Property::actionOnStop(Guest& player)
{
    if (owner->myName() == "Bankier")
    {
        buyPropertyByNewOwner(player);
        return;
    }

    if (owner->myName() != player.myName())
    {
        payRentMode->payRent(player);
        std::cout << player.myName() << " payRent to " << owner->myName() << std::endl;
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
    if (player.haveEnoughtMoney(price))
    {
        owner = &player;
        payRentMode->setNewOwner(*owner);
        player.buyProperty(price, this, district);
    }
}
