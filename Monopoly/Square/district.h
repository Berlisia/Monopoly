#pragma once
#include <vector>

class Estate;

class District
{
public:
    void assignPropertisToDistrict(const std::vector<Estate*>& propertis);
    const std::vector<Estate*>& propertis() const;
    bool operator == (const District& dist) const;

private:
    std::vector<Estate*> propertisInDistrict;
};
