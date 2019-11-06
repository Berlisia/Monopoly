#pragma once

#include "buildingMachine.h"

class AllPropertisBuildingState: public BuildingMachine
{
public:
    AllPropertisBuildingState(const CardInfo& p_card):
        card(p_card) {}

    Rent calculateRent() override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest& owner) override;

private:
    const CardInfo& card;
};
