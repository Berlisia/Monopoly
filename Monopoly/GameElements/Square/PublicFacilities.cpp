#include "PublicFacilities.h"
#include "Estate.h"
#include "Guest.h"

namespace
{
constexpr unsigned int FACTOR_OWNER_HAVE_ONE_FACILITY = 4;
constexpr unsigned int FACTOR_OWNER_HAVE_TWO_FACILITY = 10;
} // namespace

void PublicFacilities::payRent(Guest& player)
{
    auto ownerHaveSecondFacility = owner->checkPropertisInDistrict(district.propertis());
    auto rent = calculateRent(ownerHaveSecondFacility, player.rollDice());
    if (player.withdrawMoney(rent))
    {
        owner->addMoney(rent);
    } // TODO goTo bancrut if can't pay
}

void PublicFacilities::setNewOwner(Guest& newOwner)
{
    owner = &newOwner;
}

unsigned int PublicFacilities::calculateRent(unsigned int ownerHaveSecondFacility, unsigned int numberOfDice) const
{
    if (ownerHaveSecondFacility == 1)
    {
        return numberOfDice * FACTOR_OWNER_HAVE_ONE_FACILITY;
    }
    return numberOfDice * FACTOR_OWNER_HAVE_TWO_FACILITY;
}
