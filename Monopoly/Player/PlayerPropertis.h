#pragma once
#include <vector>

#include "SubjectBuildingProperty.h"

class Estate;

class PlayerPropertis
{
public:
    PlayerPropertis(const SubjectBuildingProperty& notifier) : buildingPropertyNotify(notifier) {}

    void addNew(const Estate* property, const District& district);
    unsigned int countPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict);
    const std::vector<const Estate*> snapchotPropertis();
    void remove(const Estate* property, const District& district);

private:
    std::vector<const Estate*> propertis;
    const SubjectBuildingProperty& buildingPropertyNotify;

    void notifyBuildingProperty(const District& district);
    bool findProperty(const Estate* property);
    std::vector<const Estate*>::iterator getProperty(const Estate* property);
};
