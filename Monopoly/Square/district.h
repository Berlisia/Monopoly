#pragma once
#include <vector>

class Estate;
class District
{
public:
    void assignPropertisToDistrict(const std::vector<Estate*>& propertis)
    {
        propertisInDistrict = propertis;
    }

    const std::vector<Estate*>& propertis() const
    {
        return propertisInDistrict;
    }

private:
    std::vector<Estate*> propertisInDistrict;
};

