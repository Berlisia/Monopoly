#pragma once
#include <vector>

#include "square.h"
#include "estate.h"
#include "district.h"

class PublicFacilities: public Square, public Estate
{
public: //TODO maybe this should be strategy for Property???
        // Strategy PayRentByGuest!
    PublicFacilities(const std::string& p_name, const District& p_district, unsigned int p_price):
        Estate(p_name),
        price(p_price),
        otherPublicFacilities(p_district){}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

    const std::string& estateName() override;

private:
    Guest* owner = nullptr;
    unsigned int price;
    const District& otherPublicFacilities;
};
