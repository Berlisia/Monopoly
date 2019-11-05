#include <iostream>

#include "allpropertisbuildingstate.h"
#include "housesBuildingState.h"

Rent AllPropertisBuildingState::calculateRent()
{
    return rent;
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::buyHouse(unsigned int numberOfHouses, Guest &owner)
{
    std::unique_ptr<BuildingMachine> nextState = std::make_unique<HousesBuildingState>(buildingRent);
    nextState->buyHouse(numberOfHouses, owner);
    return std::make_unique<HousesBuildingState>(std::move(nextState));
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::buyHotel(Guest &)
{
    std::cout << "You can't buy hotel when you haven't 4 houses" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(this);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::sellHouse(unsigned int , Guest &)
{
    std::cout << "You haven't houses" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(this);
}

std::unique_ptr<BuildingMachine> AllPropertisBuildingState::sellHotel(Guest&)
{
    std::cout << "You haven't hotel" << std::endl;
    return std::make_unique<AllPropertisBuildingState>(this);
}
