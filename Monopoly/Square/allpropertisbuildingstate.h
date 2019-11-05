#pragma once

#include "buildingMachine.h"

class AllPropertisBuildingState: public BuildingMachine
{
public:
    AllPropertisBuildingState(const Rent p_rent, const RentAtNumberOfBuildings& p_buildingRent):
        rent(p_rent*2),
        buildingRent(p_buildingRent){}

    Rent calculateRent() override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest& owner) override;

private:
    const Rent rent;
    const RentAtNumberOfBuildings& buildingRent;
};
