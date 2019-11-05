#pragma once

#include "housedevelop.h"
#include "buildingstate.h"

class DefaultBuildingState: public HouseDevelop, public BuildingState
{
public:
    DefaultBuildingState(const Rent p_rent): rent(p_rent) {}

    const Rent calculateRent();

    void buyHouse(unsigned int numberOfHouse, Guest&) override;
    void buyHotel(Guest&) override;
    void sellHouse(unsigned int numberOfHouse, Guest&) override;
    void sellHotel(Guest&) override;

private:
    const Rent rent;
};
