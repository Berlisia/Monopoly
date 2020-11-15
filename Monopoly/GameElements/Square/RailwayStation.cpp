#include "RailwayStation.h"
#include "Guest.h"

void RailwayStation::payRent(Guest& player)
{
    auto ownerHavePropertis = owner->checkPropertisInDistrict(district.propertis());
    if (player.withdrawMoney(rent.at(ownerHavePropertis)))
    {
        owner->addMoney(rent.at(ownerHavePropertis));
    } // TODO goTo bancrut if can't pay
}

void RailwayStation::setNewOwner(Guest& newOwner)
{
    owner = &newOwner;
}
