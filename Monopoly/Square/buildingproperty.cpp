#include "buildingproperty.h"
#include "guest.h"

namespace{
constexpr unsigned int MAX_NUMBER_OF_HOUSES = 4;
constexpr unsigned int HOTEL = 5;
}

void BuildingProperty::payRent(Guest &player, Guest &owner) const
{
    auto tmpRent = rent;
    if(numberOfHouses != 0)
    {
        tmpRent  = buildingRent.at(numberOfHouses);
    }
    else
    {
        if(haveAllPropertisFromDistrict(owner))
        {
            tmpRent = rent * 2;
        }
    }
    withdrawRent(tmpRent, player, owner);
}

void BuildingProperty::buyHouse(unsigned int numberOfNewHouses, Guest& owner)
{
    if(haveAllPropertisFromDistrict(owner) && canBuyNewHouses(numberOfNewHouses))
    {
        if(owner.withdrawMoney(numberOfNewHouses * housePrice))
        {
            numberOfHouses += numberOfNewHouses;
        }
    }
}

void BuildingProperty::withdrawRent(Rent newRent, Guest &player, Guest &owner) const
{
    if(player.withdrawMoney(newRent)) //TODO bancrut
    {
        owner.addMoney(newRent);
    }
}

bool BuildingProperty::haveAllPropertisFromDistrict(Guest& owner) const
{
    return owner.checkPropertisInDistrict(district.propertis()) == district.propertis().size();
}

bool BuildingProperty::canBuyNewHouses(unsigned int numberOfNewHouses) const
{
    auto housesAfterAdd = numberOfHouses + numberOfNewHouses;

    auto haveHausesLessThanMax = numberOfNewHouses <= MAX_NUMBER_OF_HOUSES;
    auto housesAfterAddIsLessThanMax = housesAfterAdd <= MAX_NUMBER_OF_HOUSES;

    return haveHausesLessThanMax && housesAfterAddIsLessThanMax;
}
