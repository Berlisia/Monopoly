#pragma once
#include <variant>

struct WithoutOwner
{
};
struct Default
{
};
struct AllPropertis
{
};
struct HouseBuilding
{
    unsigned int numberOfHouses = 0;
};
struct HotelBuilding
{
};
struct Mortgage
{
};

using StateBuilding = std::variant<WithoutOwner, Default, AllPropertis, HouseBuilding, HotelBuilding, Mortgage>;
