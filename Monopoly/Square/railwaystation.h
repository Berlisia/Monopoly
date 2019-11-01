#pragma once
#include <map>

#include "rentpaymode.h"
#include "district.h"

typedef std::map<unsigned int, unsigned int> RentAtNumberOfRailways;

class RailwayStation: public RentPayMode
{
public:
    RailwayStation(const RentAtNumberOfRailways& p_rent, const District& p_district):
        rent(p_rent),
        district(p_district) {}

    void payRent(Guest& player, Guest& owner) const override;

private:
    const RentAtNumberOfRailways rent;
    const District& district;
};
