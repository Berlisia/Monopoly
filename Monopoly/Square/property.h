#pragma once
#include <memory>

#include "square.h"

class Property: public Square
{
public:
    Property(unsigned int p_price, unsigned int p_rent):
        price(p_price),
        rent(p_rent)
    {
    }
    virtual void actionOnStop(Player&);
    virtual void actionOnWalkThrought(Player&);

private:
    unsigned int price;
    unsigned int rent;
    Player* owner = nullptr;

    void buyPropertyByNewOwner(Player& player);
    void payRentByGuest(Player& player);
};
