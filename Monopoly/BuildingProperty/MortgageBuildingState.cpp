#include <iostream>
#include <cmath>

#include "MortgageBuildingState.h"
#include "Square/district.h"
#include "guest.h"
#include "allpropertisbuildingstate.h"
#include "defultbuildingstate.h"

namespace {
constexpr Rent RENT_FOR_MORTGAGE = 0;

}
Rent MortgageBuildingState::calculateRent() const
{
    return RENT_FOR_MORTGAGE;
}

std::unique_ptr<BuildingMachine> MortgageBuildingState::buyHouse(unsigned int numberOfHouse, Guest &)
{
    std::cout << "You can't buy house when you have mortgage" << std::endl;
    return std::make_unique<MortgageBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> MortgageBuildingState::buyHotel(Guest &)
{
    std::cout << "You can't buy hotel when you have mortgage" << std::endl;
    return std::make_unique<MortgageBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> MortgageBuildingState::sellHouse(unsigned int numberOfHouse, Guest &)
{
    std::cout << "You haven't houses" << std::endl;
    return std::make_unique<MortgageBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> MortgageBuildingState::sellHotel(Guest &)
{
    std::cout << "You haven't hotel" << std::endl;
    return std::make_unique<MortgageBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> MortgageBuildingState::mortgage(Guest &owner)
{
    std::cout << "You have mortgage" << std::endl;
    return std::make_unique<MortgageBuildingState>(*this);
}

std::unique_ptr<BuildingMachine> MortgageBuildingState::relieveMortgage(Guest &owner)
{
    auto mortgage = card.mortgagePrice * 1.1;
    owner.withdrawMoney(std::round(mortgage));
    if(owner.checkPropertisInDistrict(district.propertis()) == district.propertis().size())
    {
        return std::make_unique<AllPropertisBuildingState>(card, district);
    }
    return std::make_unique<DefaultBuildingState>(card, district);
}
