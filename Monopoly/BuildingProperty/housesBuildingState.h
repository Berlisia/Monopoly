#pragma once

#include "buildingMachine.h"
#include "Square/district.h"

class HousesBuildingState: public BuildingMachine
{
public:
    HousesBuildingState(const CardInfo& p_card, const District& p_district):
        card(p_card),
        district(p_district){}

    Rent calculateRent() const override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> mortgage(Guest& owner) override;
    std::unique_ptr<BuildingMachine> relieveMortgage(Guest& owner) override;


private:
    const CardInfo& card;
    const District& district;
    unsigned int numberOfHouses = 0;

    std::unique_ptr<BuildingMachine> sellAllHouses(Guest& owner);
    std::unique_ptr<BuildingMachine> sellSomeHouses(unsigned int houses, Guest& owner);
    std::unique_ptr<BuildingMachine> yourself();
};
