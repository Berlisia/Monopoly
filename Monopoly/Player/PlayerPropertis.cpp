#include <algorithm>

#include "Estate.h"
#include "PlayerPropertis.h"

void PlayerPropertis::addNew(const Estate* property, const District& district)
{
    propertis.push_back(property);
    notifyBuildingProperty(district);
}

unsigned int PlayerPropertis::countPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict)
{
    unsigned int countPropertisFromDistrict = 0;
    for (const auto districtProperty : propertisInDistrict)
    {
        if (findProperty(districtProperty))
        {
            countPropertisFromDistrict++;
        }
    }
    return countPropertisFromDistrict;
}

const std::vector<const Estate*> PlayerPropertis::snapchotPropertis()
{
    return propertis;
}

void PlayerPropertis::remove(const Estate* property, const District& district)
{
    if (findProperty(property))
    {
        propertis.erase(getProperty(property));
        buildingPropertyNotify.notifyForNotAllPropertis(district);
    }
}

void PlayerPropertis::notifyBuildingProperty(const District& district)
{
    auto allPropertis = countPropertisInDistrict(district.propertis());
    if (allPropertis == district.propertis().size())
    {
        buildingPropertyNotify.notifyForHaveAllPropertis(district);
    }
}

bool PlayerPropertis::findProperty(const Estate* property)
{
    return std::find_if(propertis.begin(), propertis.end(), [property](const Estate* playerProperty) {
               return *property == *playerProperty;
           }) != propertis.end();
}

std::vector<const Estate*>::iterator PlayerPropertis::getProperty(const Estate* property)
{
    return std::find_if(propertis.begin(), propertis.end(), [property](const Estate* playerProperty) {
        return *property == *playerProperty;
    });
}
