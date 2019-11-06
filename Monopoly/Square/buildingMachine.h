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
};

class BuildingMachine
{
public:
    virtual ~BuildingMachine() = default;

    virtual Rent calculateRent() = 0;
    virtual std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest& owner) = 0;
    virtual std::unique_ptr<BuildingMachine> buyHotel(Guest& owner) = 0;
    virtual std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest& owner) = 0;
    virtual std::unique_ptr<BuildingMachine> sellHotel(Guest& owner) = 0;

};
