#pragma once

#include "buildingMachine.h"

class HotelBuildingState: public BuildingMachine
{
public:
    HotelBuildingState(const Rent p_rentForHotel, const RentAtNumberOfBuildings& p_buildingRent,
                       unsigned int p_hotelPrice, unsigned int p_housePrice):
        rent(p_rentForHotel),
        buildingRent(p_buildingRent),
        hotelPrice(p_hotelPrice),
        housePrice(p_housePrice){}

    Rent calculateRent() override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest& owner) override;

private:
    const Rent rent;
    const RentAtNumberOfBuildings& buildingRent;
    const unsigned int hotelPrice;
    const unsigned int housePrice;
};
