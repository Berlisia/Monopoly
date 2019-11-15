#include <iostream>

#include "HotelBuildingState.h"
#include "guest.h"
#include "MortgageBuildingState.h"

namespace{
constexpr unsigned int HOTEL = 5;
}

Rent HotelBuildingState::calculateRent() const
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
    HousesBuildingState newState(card, district);
    sellHotelAndGetFourHouses(owner, newState);
    return std::make_unique<HousesBuildingState>(newState);
}

std::unique_ptr<BuildingMachine> HotelBuildingState::mortgage(Guest &)
{
    std::cout << "Firstly sell all buildings" << std::endl;
    return std::make_unique<HotelBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> HotelBuildingState::relieveMortgage(Guest&)
{
    std::cout << "You haven't mortage" << std::endl;
    return std::make_unique<HotelBuildingState>(*this);
}

void HotelBuildingState::sellAll(Guest& owner)
{
    owner.addMoney((card.hotelPrice + card.housePrice * 4)/2);
    owner.addMoney(card.mortgagePrice);
}

void HotelBuildingState::sellHotelAndGetFourHouses(Guest& owner, HousesBuildingState& newState)
{
    owner.addMoney(card.hotelPrice / 2);
    owner.addMoney(card.housePrice * 4);
    newState.buyHouse(4, owner);
}
