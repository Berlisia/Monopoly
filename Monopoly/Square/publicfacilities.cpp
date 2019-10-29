#include "publicfacilities.h"
#include "player.h"

void PublicFacilities::actionOnStop(Guest& player)
{
    if(owner)
    {
        if(not (owner->myName() == player.myName()))
        {
            auto ownerHavePropertis = owner->checkPropertisInDistrict(otherPublicFacilities.propertis());
        }
    }
    else
    {
        if(player.buyProperty(price, this))
        {
            owner = &player;
        }
    }
}

void PublicFacilities::actionOnWalkThrought(Guest &)
{
}

const std::string PublicFacilities::squareName()
{
    return name;
}

const std::string &PublicFacilities::estateName()
{
    return name;
}
