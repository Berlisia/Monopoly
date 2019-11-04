#pragma once
#include <map>

#include "rentpaymode.h"
#include "district.h"

typedef unsigned int Rent;
typedef std::map<unsigned int, Rent> RentAtNumberOfBuildings;

class HouseDevelop
{
public:
    virtual ~HouseDevelop() = default;

    virtual void buyHouse(unsigned int numberOfHouse, Guest& owner) = 0;
};

class BuildingProperty: public RentPayMode, public HouseDevelop
{
public:
    BuildingProperty(const Rent p_rent, const RentAtNumberOfBuildings& p_buildingRent, const District& p_district,
                     unsigned int p_housePrice, unsigned int p_hotelPrice):
        rent(p_rent),
        buildingRent(p_buildingRent),
        district(p_district),
        housePrice(p_housePrice),
        hotelPrice(p_hotelPrice) {}

    void payRent(Guest& player, Guest& owner) const override;

    void buyHouse(unsigned int numberOfHouse, Guest& owner) override;
private:
    const Rent rent;
    const RentAtNumberOfBuildings buildingRent;
    const District& district;

    const unsigned int housePrice;
    const unsigned int hotelPrice;

    unsigned int numberOfHouses = 0;
    bool hotel = false;

    void withdrawRent(Rent rent, Guest &player, Guest &owner) const;
};
