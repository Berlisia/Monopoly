#pragma once

typedef unsigned int Rent;

class Guest;
class HouseDevelop
{
public:
    virtual ~HouseDevelop() = default;

    virtual void buyHouse(unsigned int numberOfHouse, Guest& owner) = 0;
    virtual void buyHotel(Guest& owner) = 0;
    virtual void sellHouse(unsigned int numberOfHouse, Guest& owner) = 0;
    virtual void sellHotel(Guest& owner) = 0;
};
