#include "district.h"
#include "estate.h"

void District::assignPropertisToDistrict(const std::vector<Estate *> &propertis)
{
    propertisInDistrict = propertis;
}

const std::vector<Estate *> &District::propertis() const
{
    return propertisInDistrict;
}

bool District::operator ==(const District &dist) const
{
    if(propertisInDistrict.size() != dist.propertisInDistrict.size())
        return false;

    for(unsigned int i; i < propertisInDistrict.size(); ++i)
    {
        if(*(dist.propertisInDistrict[i]) != *(propertisInDistrict[i]))
            return false;
    }
    return true;
}
