#include "housesBuildingState.h"
#include "guest.h"
#include "HotelBuildingState.h"
#include "allpropertisbuildingstate.h"

namespace{
constexpr unsigned int MAX_NUMBER_OF_HOUSES = 4;
constexpr unsigned int HOTEL = 5;
}

Rent HousesBuildingState::calculateRent()
{
    return buildingRent.at(numberOfHouses);
}

std::unique_ptr<BuildingMachine> HousesBuildingState::buyHouse(unsigned int numberOfNewHouses, Guest& owner)
{
    auto numberOfHausesAfterAdd = numberOfHouses + numberOfNewHouses;
    if(numberOfHouses <= MAX_NUMBER_OF_HOUSES and numberOfHausesAfterAdd <= MAX_NUMBER_OF_HOUSES)
    {
        owner.withdrawMoney(numberOfNewHouses * housePrice);
        numberOfHouses = numberOfHausesAfterAdd;
    }
    return yourself();
}

std::unique_ptr<BuildingMachine> HousesBuildingState::buyHotel(Guest& owner)
{
    if(numberOfHouses == MAX_NUMBER_OF_HOUSES)
    {
        std::unique_ptr<BuildingMachine> newState =
                std::make_unique<HotelBuildingState>(buildingRent.at(HOTEL), buildingRent, hotelPrice, housePrice);
        newState->buyHotel(owner);
        return std::make_unique<HotelBuildingState>(newState);
    }
    std::cout << "You can't buy hotel when haven't 4 houses" << std::endl;
    return yourself();
}

std::unique_ptr<BuildingMachine> HousesBuildingState::sellHouse(unsigned int houses, Guest& owner)
{
    int housesAfterSell = int(numberOfHouses - houses);
    if(housesAfterSell > 0)
    {
        return sellSomeHouses(houses, owner);
    }

    if(housesAfterSell == 0)
    {
        return sellAllHouses(owner);
    }

    std::cout << "You want to sell more houses than you have" << std::endl;
    return yourself();
}

std::unique_ptr<BuildingMachine> HousesBuildingState::sellHotel(Guest &)
{
    std::cout << "You haven't hetel" << std::endl;
    return yourself();
}

std::unique_ptr<BuildingMachine> HousesBuildingState::sellAllHouses(Guest& owner)
{
    owner.addMoney(numberOfHouses * housePrice/2);
    return std::make_unique<AllPropertisBuildingState>(rent, buildingRent);
}

std::unique_ptr<BuildingMachine> HousesBuildingState::sellSomeHouses(unsigned int houses, Guest &owner)
{
    owner.addMoney(houses * housePrice/2);
    numberOfHouses -= houses;
    return yourself();
}

std::unique_ptr<BuildingMachine> HousesBuildingState::yourself()
{
    return std::make_unique<HousesBuildingState>(this);
}
