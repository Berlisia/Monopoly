#pragma once

#include "buildingMachine.h"

class DefaultBuildingState: public BuildingMachine
{
public:
    DefaultBuildingState(const Rent p_rent): rent(p_rent) {}

    Rent calculateRent() override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest&) override;

private:
    const Rent rent;
};
