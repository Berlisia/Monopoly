#pragma once

class District;

class BuildingObserver
{
public:
    virtual ~BuildingObserver() = default;
    virtual void updateForAllPropertis() = 0;
    virtual void updateForNotAllPropertis() = 0;
    virtual const District& getDistrict() = 0;
};
