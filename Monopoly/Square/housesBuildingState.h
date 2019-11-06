#pragma once

#include "buildingMachine.h"

class HousesBuildingState: public BuildingMachine
{
public:
    HousesBuildingState(const CardInfo& p_card):
        card(p_card){}

    Rent calculateRent() override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest&) override;

private:
    const CardInfo& card;
    unsigned int numberOfHouses = 0;

    std::unique_ptr<BuildingMachine> sellAllHouses(Guest& owner);
    std::unique_ptr<BuildingMachine> sellSomeHouses(unsigned int houses, Guest& owner);
    std::unique_ptr<BuildingMachine> yourself();
};
