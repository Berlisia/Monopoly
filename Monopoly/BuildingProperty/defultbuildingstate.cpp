#include <iostream>

#include "defultbuildingstate.h"
#include "MortgageBuildingState.h"
#include "guest.h"

Rent DefaultBuildingState::calculateRent() const
{
    return card.rent;
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
    std::cout << "You haven't houses" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::sellHotel(Guest&)
{
    std::cout << "You haven't hotel" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::mortgage(Guest &owner)
{
    owner.addMoney(card.mortgagePrice);
    return std::make_unique<MortgageBuildingState>(district, card);
}

std::unique_ptr<BuildingMachine> DefaultBuildingState::relieveMortgage(Guest &)
{
    std::cout << "You haven't mortgege on this property" << std::endl;
    return std::make_unique<DefaultBuildingState>(*this);
}
