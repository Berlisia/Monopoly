#pragma once

#include "buildingMachine.h"

class HousesBuildingState: public BuildingMachine
{
public:
    HousesBuildingState(Rent p_rent, const RentAtNumberOfBuildings& p_buildingrent,
                        unsigned int p_housePrice, unsigned int p_hotelPrice):
        rent(p_rent),
        buildingRent(p_buildingrent),
        housePrice(p_housePrice),
        hotelPrice(p_hotelPrice) {}

    Rent calculateRent() override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest&) override;

private:
    const Rent rent;
    const RentAtNumberOfBuildings& buildingRent;
    unsigned int numberOfHouses = 0;
    unsigned int housePrice;
    unsigned int hotelPrice;

    std::unique_ptr<BuildingMachine> sellAllHouses(Guest& owner);
    std::unique_ptr<BuildingMachine> sellSomeHouses(unsigned int houses, Guest& owner);
    std::unique_ptr<BuildingMachine> yourself();
};
