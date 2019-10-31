#pragma once
#include <vector>

#include "rentpaymode.h"
#include "district.h"

namespace{
constexpr unsigned int FACTOR_OWNER_HAVE_ONE_FACILITY = 4;
constexpr unsigned int FACTOR_OWNER_HAVE_TWO_FACILITY = 10;
}

class Estate;

class PublicFacilities: public RentPayMode
{
public:
    PublicFacilities(const District& p_district): district(p_district) {}

    void payRent(Guest& player, Guest& owner) const override;

private:
    const District& district;

    unsigned int calculateRent(unsigned int, unsigned int numberOfDice);
};
