#pragma once
#include <vector>

class Estate;

class District
{
public:
    void assignPropertyToDistrict(const Estate* property);
    void assignPropertisToDistrict(const std::vector<const Estate*>& propertis);
    const std::vector<const Estate*>& propertis() const;
    bool operator==(const District& dist) const;

private:
    std::vector<const Estate*> propertisInDistrict = {};
};
