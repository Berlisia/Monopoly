#pragma once
#include <map>

#include "rentpaymode.h"
#include "district.h"

typedef std::map<unsigned int, unsigned int> Rent;

class BuildingProperty: public RentPayMode
{
public:
    BuildingProperty(const Rent& p_rent, const District& p_district):
        rent(p_rent),
        district(p_district) {}

    void payRent(Guest& player, Guest& owner) const override;

private:
    const Rent rent;
    const District& district;
};
