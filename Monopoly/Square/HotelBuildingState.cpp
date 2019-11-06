#include <iostream>

#include "HotelBuildingState.h"
#include "housesBuildingState.h"
#include "guest.h"

namespace{
constexpr unsigned int HOTEL = 5;
}

Rent HotelBuildingState::calculateRent()
{
    return card.buildingRent.at(HOTEL);
}

std::unique_ptr<BuildingMachine> HotelBuildingState::buyHouse(unsigned int, Guest&)
{
    std::cout << "You can't buy houses for property which have hotel" << std::endl;
    return std::make_unique<HotelBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> HotelBuildingState::buyHotel(Guest&)
{
    std::cout << "You can have one hotel per property" << std::endl;
    return std::make_unique<HotelBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> HotelBuildingState::sellHouse(unsigned int, Guest&)
{
    std::cout << "You haven't houses" << std::endl;
    return std::make_unique<HotelBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> HotelBuildingState::sellHotel(Guest &owner)
{
    std::unique_ptr<HousesBuildingState> newState = std::make_unique<HousesBuildingState>(card);
    owner.addMoney(card.hotelPrice / 2);
    owner.addMoney(card.housePrice * 4);
    newState->buyHouse(4, owner); //TODO 4 houses or nothing
    return std::make_unique<HousesBuildingState>(*newState);
}
