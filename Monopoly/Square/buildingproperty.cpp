#include "buildingproperty.h"
#include "guest.h"
#include "allpropertisbuildingstate.h"

void BuildingProperty::payRent(Guest& player, Guest& owner) const
{
    withdrawRent(currentState->calculateRent(), player, owner);
}

void BuildingProperty::buyHouse(unsigned int numberOfNewHouses, Guest& owner)
{
    currentState = currentState->buyHouse(numberOfNewHouses, owner);
}

void BuildingProperty::buyHotel(Guest& owner)
{
    currentState = currentState->buyHotel(owner);
}

void BuildingProperty::sellHouse(unsigned int numberOfHouse, Guest &owner)
{
    currentState = currentState->sellHouse(numberOfHouse, owner);
}

void BuildingProperty::sellHotel(Guest& owner)
{
    currentState = currentState->sellHotel(owner);
}

void BuildingProperty::updateForAllPropertis()
{
    currentState = std::make_unique<AllPropertisBuildingState>(card);
}

void BuildingProperty::updateForNotAllPropertis()
{
    currentState = std::make_unique<DefaultBuildingState>(card.rent);
}

const District &BuildingProperty::getDistrict()
{
    return district;
}

void BuildingProperty::withdrawRent(Rent newRent, Guest &player, Guest &owner) const
{
    if(player.withdrawMoney(newRent)) //TODO bancrut
    {
        owner.addMoney(newRent);
    }
}

bool BuildingProperty::haveAllPropertisFromDistrict(Guest& owner) const
{
    return owner.checkPropertisInDistrict(district.propertis()) == district.propertis().size();
}
