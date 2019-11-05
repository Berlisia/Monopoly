#include <iostream>

#include "defultbuildingstate.h"

const Rent DefaultBuildingState::calculateRent()
{
    return rent;
}

void DefaultBuildingState::buyHouse(unsigned int numberOfHouse, Guest&)
{
    std::cout << "You can't buy house when you haven't all propertis from district" << std::endl;
}

void DefaultBuildingState::buyHotel(Guest&)
{
    std::cout << "You can't buy hotel when you haven't 4 houses" << std::endl;
}

void DefaultBuildingState::sellHouse(unsigned int numberOfHouse, Guest&)
{
    std::cout << "You havn't houses" << std::endl;
}

void DefaultBuildingState::sellHotel(Guest&)
{
    std::cout << "You havn't hotel" << std::endl;
}
