#pragma once
#include <memory>
#include <map>

#include "square.h"
#include "district.h"

typedef std::map<unsigned int, unsigned int> Rent;

class Player;

class Property: public Square
{
public:
    Property(const District& p_district, unsigned int p_price, const Rent p_rent, const std::string p_name):
        district(p_district),
        price(p_price),
        rent(p_rent),
        name(p_name) {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

    bool operator == (const Property& prop) const;

private:
    const District& district;
    unsigned int price;
    const Rent rent;
    const std::string name;

    Guest* owner = nullptr;

    void buyPropertyByNewOwner(Guest& player);
    void payRentByGuest(Guest& player);
};
