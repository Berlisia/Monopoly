#pragma once

#include "housedevelop.h"

class AllPropertisBuildingState: public HouseDevelop
{
public:
    AllPropertisBuildingState(const Rent p_rent): rent(p_rent*2) {}

    const Rent calculateRent();

    void buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    void buyHotel(Guest& owner) override;
    void sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    void sellHotel(Guest& owner) override;

private:
    const Rent rent;
};


const Rent AllPropertisBuildingState::calculateRent()
{
    return rent;
}

void AllPropertisBuildingState::buyHouse(unsigned int numberOfHouse, Guest &owner)
{

}

void AllPropertisBuildingState::buyHotel(Guest &owner)
{

}

void AllPropertisBuildingState::sellHouse(unsigned int numberOfHouse, Guest &owner)
{

}

void AllPropertisBuildingState::sellHotel(Guest&)
{
    std::cout << "You havn't hotel" << std::endl;
}
