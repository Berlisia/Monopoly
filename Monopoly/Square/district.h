#pragma once
#include <vector>

class Property;
class District
{
public:
    void assignPropertisToDistrict(const std::vector<Property*>& propertis)
    {
        propertisInDistrict = propertis;
    }

private:
    std::vector<Property*> propertisInDistrict;
};

