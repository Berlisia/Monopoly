#include <iostream>

#include "defultbuildingstate.h"

Rent DefaultBuildingState::calculateRent()
{
    return rent;
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::buyHouse(unsigned int, Guest&)
{
    std::cout << "You can't buy house when you haven't all propertis from district" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::buyHotel(Guest&)
{
    std::cout << "You can't buy hotel when you haven't 4 houses" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::sellHouse(unsigned int, Guest&)
{
    std::cout << "You havn't houses" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::sellHotel(Guest&)
{
    std::cout << "You havn't hotel" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}
