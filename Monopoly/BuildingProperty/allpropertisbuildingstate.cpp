#include <iostream>

#include "allpropertisbuildingstate.h"
#include "housesBuildingState.h"
#include "MortgageBuildingState.h"
#include "guest.h"

Rent AllPropertisBuildingState::calculateRent() const
{
    return card.rent*2;
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::buyHouse(unsigned int numberOfHouses, Guest &owner)
{
    HousesBuildingState nextState(card, district);
    nextState.buyHouse(numberOfHouses, owner);
    return std::make_unique<HousesBuildingState>(nextState);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::buyHotel(Guest &)
{
    std::cout << "You can't buy hotel when you haven't 4 houses" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::sellHouse(unsigned int , Guest &)
{
    std::cout << "You haven't houses" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::sellHotel(Guest&)
{
    std::cout << "You haven't hotel" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::mortgage(Guest &owner)
{
    owner.addMoney(card.mortgagePrice);
    return std::make_unique<MortgageBuildingState>(district, card);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::relieveMortgage(Guest &)
{
    std::cout << "You haven't mortgege on this property" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(*this);
}
