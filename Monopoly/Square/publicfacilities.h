#pragma once
#include <vector>

#include "rentpaymode.h"
#include "district.h"

class PublicFacilities: public RentPayMode
{
public:
    PublicFacilities(const District& p_district): district(p_district) {}

    void payRent(Guest& player) const override;
    void setNewOwner(Guest& owner) override;

private:
    const District& district;
    Guest* owner;

    unsigned int calculateRent(unsigned int, unsigned int numberOfDice) const;
};
