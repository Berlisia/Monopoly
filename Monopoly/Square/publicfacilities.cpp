#include "publicfacilities.h"
#include "estate.h"
#include "guest.h"

void PublicFacilities::payRent(Guest& player, Guest& owner) const
{
    auto ownerHaveSecondFacility = owner.checkPropertisInDistrict(district.propertis());
    auto rent = calculateRent(ownerHaveSecondFacility, player.rollDice());
    auto money = player.withdrawMoney(rent);
    owner.addMoney(money);
}

unsigned int PublicFacilities::calculateRent(unsigned int ownerHaveSecondFacility, unsigned int numberOfDice)
{
    auto rent = 0;
    if(ownerHaveSecondFacility == 0)
    {
        rent = numberOfDice * FACTOR_OWNER_HAVE_ONE_FACILITY;
    }
    rent = numberOfDice * FACTOR_OWNER_HAVE_TWO_FACILITY;
}
