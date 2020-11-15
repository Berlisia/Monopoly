#include "SubjectBuildingProperty.h"

void SubjectBuildingProperty::attach(BuildingObserver* buildingProp)
{
    buildingPropertis.push_back(buildingProp);
}

void SubjectBuildingProperty::notifyForHaveAllPropertis(const District& district) const
{
    for (auto observer : buildingPropertis)
    {
        if ((*observer).getDistrict() == district)
        {
            observer->updateForAllPropertis();
        }
    }
}

void SubjectBuildingProperty::notifyForNotAllPropertis(const District& district) const
{
    for (auto observer : buildingPropertis)
    {
        if ((*observer).getDistrict() == district)
        {
            observer->updateForNotAllPropertis();
        }
    }
}
