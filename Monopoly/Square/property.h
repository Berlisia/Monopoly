#pragma once
#include <memory>

#include "square.h"

class Player;

class Property: public Square
{
public:
    Property(unsigned int p_price, unsigned int p_rent):
        price(p_price),
        rent(p_rent)
    {
    }
    virtual void actionOnStop(Guest&);
    virtual void actionOnWalkThrought(Guest&);

private:
    unsigned int price;
    unsigned int rent;
    Guest* owner = nullptr;

    void buyPropertyByNewOwner(Guest& player);
    void payRentByGuest(Guest& player);
};
