#include "District.h"
#include "Estate.h"

void District::assignPropertyToDistrict(const Estate* property)
{
    propertisInDistrict.push_back(property);
}

void District::assignPropertisToDistrict(const std::vector<const Estate*>& propertis)
{
    propertisInDistrict = propertis;
}

const std::vector<const Estate*>& District::propertis() const
{
    return propertisInDistrict;
}

bool District::operator==(const District& dist) const
{
    if (propertisInDistrict.size() != dist.propertisInDistrict.size()) return false;

    for (unsigned int i = 0; i < propertisInDistrict.size(); ++i)
    {
        if (*(dist.propertisInDistrict[i]) != *(propertisInDistrict[i])) return false;
    }
    return true;
}
