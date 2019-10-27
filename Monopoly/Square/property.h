#pragma once
#include <memory>

#include "square.h"

class Player;

class Property: public Square
{
public:
    Property(unsigned int p_price, unsigned int p_rent, const std::string p_name):
        price(p_price),
        rent(p_rent),
        name(p_name) {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

private:
    unsigned int price;
    unsigned int rent;
    const std::string name;

    Guest* owner = nullptr;

    void buyPropertyByNewOwner(Guest& player);
    void payRentByGuest(Guest& player);
};
