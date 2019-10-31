#include "buildingproperty.h"
#include "guest.h"

void BuildingProperty::payRent(Guest &player, Guest &owner) const
{
    auto ownerHavePropertis = owner.checkPropertisInDistrict(district.propertis());
    auto money = player.withdrawMoney(rent.at(ownerHavePropertis));
    owner.addMoney(money);
}
