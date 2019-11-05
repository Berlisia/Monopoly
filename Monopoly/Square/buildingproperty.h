#pragma once
#include <map>

#include "rentpaymode.h"
#include "district.h"
#include "housedevelop.h"

#include "defultbuildingstate.h"

typedef std::map<unsigned int, Rent> RentAtNumberOfBuildings;

class BuildingProperty: public RentPayMode, public HouseDevelop
{
public:
    BuildingProperty(const Rent p_rent, const RentAtNumberOfBuildings& p_buildingRent, const District& p_district,
                     unsigned int p_housePrice, unsigned int p_hotelPrice):
        rent(p_rent),
        buildingRent(p_buildingRent),
        district(p_district),
        housePrice(p_housePrice),
        hotelPrice(p_hotelPrice),
        currentState(std::make_unique<DefaultBuildingState>(p_rent)) {}

    void payRent(Guest& player, Guest& owner) const override;

    void buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    void buyHotel(Guest& owner) override;
    void sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    void sellHotel(Guest& owner) override;
private:
    const Rent rent;
    const RentAtNumberOfBuildings buildingRent;
    const District& district;

    std::unique_ptr<HouseDevelop> currentState;

    const unsigned int housePrice;
    const unsigned int hotelPrice;

    unsigned int numberOfHouses = 0;

    void withdrawRent(Rent rent, Guest &player, Guest &owner) const;
    bool haveAllPropertisFromDistrict(Guest& owner) const;
    bool canBuyNewHouses(unsigned int numberOfNewHouses) const;
};
