#pragma once
#include <memory>
#include <map>

#include "square.h"
#include "estate.h"
#include "district.h"

typedef std::map<unsigned int, unsigned int> Rent;

class Player;

class Property: public Square, public Estate
{
public:
    Property(const District& p_district, unsigned int p_price, const Rent p_rent, const std::string p_name):
        Estate(p_name),
        district(p_district),
        price(p_price),
        rent(p_rent){}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

    const std::string& estateName() override;

private:
    const District& district;
    unsigned int price;
    const Rent rent;

    Guest* owner = nullptr;

    void buyPropertyByNewOwner(Guest& player);
    void payRentByGuest(Guest& player);
};
