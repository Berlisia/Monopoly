#include "railwaystation.h"
#include "guest.h"

void RailwayStation::payRent(Guest &player, Guest &owner) const
{
    auto ownerHavePropertis = owner.checkPropertisInDistrict(district.propertis());
    if(player.withdrawMoney(rent.at(ownerHavePropertis)))
    {
        owner.addMoney(rent.at(ownerHavePropertis));
    }//TODO goTo bancrut if can't pay
}
