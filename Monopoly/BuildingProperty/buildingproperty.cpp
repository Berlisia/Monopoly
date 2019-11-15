#include "buildingproperty.h"
#include "guest.h"
#include "allpropertisbuildingstate.h"

#include <memory>

void BuildingProperty::payRent(Guest& player) const
{
//    if(fsm){
//        const auto& state = fsm->get_state();
//        withdrawRent(std::get<BuildingMachine>(state).calculateRent(), player, owner);
//    }
    withdrawRent(currentState->calculateRent(), player);
}

void BuildingProperty::setNewOwner(Guest& newOwner)
{
    owner = &newOwner;
    if(owner != nullptr){
//        fsm.emplace(card, *owner);
    }
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

void BuildingProperty::mortgage(Guest &owner)
{
    currentState = currentState->mortgage(owner);
}

void BuildingProperty::relieveMortgage(Guest &owner)
{
    currentState = currentState->relieveMortgage(owner);
}

void BuildingProperty::updateForAllPropertis()
{
    currentState = std::make_unique<AllPropertisBuildingState>(card, district);
}

void BuildingProperty::updateForNotAllPropertis()
{
    currentState = std::make_unique<DefaultBuildingState>(card, district);
}

const District &BuildingProperty::getDistrict()
{
    return district;
}

void BuildingProperty::withdrawRent(Rent newRent, Guest &player) const
{
    if(player.withdrawMoney(newRent)) //TODO bancrut
    {
        owner->addMoney(newRent);
    }
}
