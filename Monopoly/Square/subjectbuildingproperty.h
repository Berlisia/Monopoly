#pragma once
#include "buildingproperty.h"

class SubjectBuildingProperty
{
public:
    void attach(BuildingObserver* buildingProp);
    void notifyForHaveAllPropertis(const District& district) const;

private:
    std::vector<BuildingObserver*> buildingPropertis;
};
