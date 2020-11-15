#pragma once
#include <memory>
#include <map>

class HouseDevelop;
class Guest;

typedef unsigned int Rent;
typedef std::map<unsigned int, Rent> RentAtNumberOfBuildings;

struct CardInfo
{
    const Rent rent;
    const RentAtNumberOfBuildings buildingRent;
    unsigned int housePrice;
    unsigned int hotelPrice;
    unsigned int mortgagePrice;
};
