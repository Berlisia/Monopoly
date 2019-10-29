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

    const std::vector<Property*>& propertis() const
    {
        return propertisInDistrict;
    }

private:
    std::vector<Property*> propertisInDistrict;
};

