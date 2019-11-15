#pragma once

#include "buildingMachine.h"
#include "housesBuildingState.h"

class HotelBuildingState: public BuildingMachine
{
public:
    HotelBuildingState(const CardInfo& p_card, const District& p_district):
        card(p_card),
        district(p_district){}

    Rent calculateRent() const override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest& owner) override;
    std::unique_ptr<BuildingMachine> mortgage(Guest& owner) override;
    std::unique_ptr<BuildingMachine> relieveMortgage(Guest& owner) override;
private:
    const CardInfo& card;
    const District& district;


    void sellAll(Guest& owner);
    void sellHotelAndGetFourHouses(Guest& owner, HousesBuildingState& newState);
};
