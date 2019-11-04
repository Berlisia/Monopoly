#include "buildingproperty.h"
#include "guest.h"

namespace{
constexpr unsigned int MAX_NUMBER_OF_HOUSES = 4;
}

void BuildingProperty::payRent(Guest &player, Guest &owner) const
{
    auto ownerHavePropertis = owner.checkPropertisInDistrict(district.propertis());
    if(ownerHavePropertis == district.propertis().size())
    {
        withdrawRent(rent * 2, player, owner);
        return;
    }
    withdrawRent(rent, player, owner);
}

void BuildingProperty::buyHouse(unsigned int numberOfNewHouses, Guest& owner)
{
    if(numberOfNewHouses <= MAX_NUMBER_OF_HOUSES)
    {
        auto houses = numberOfHouses + numberOfNewHouses;
        if(houses <= MAX_NUMBER_OF_HOUSES)
        {
            if(owner.withdrawMoney(numberOfNewHouses * housePrice))
            {
                numberOfHouses = houses;
            }
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
