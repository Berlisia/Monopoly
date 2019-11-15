#pragma once

#include "buildingMachine.h"
#include "Square/district.h"
//#include "EventVariant.h"
//#include "StateVariant.h"

class DefaultBuildingState: public BuildingMachine
{
public:
    DefaultBuildingState(const CardInfo& p_rent, const District& p_district):
        card(p_rent),
        district(p_district){}

    Rent calculateRent() const override;

    std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> buyHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse, Guest&) override;
    std::unique_ptr<BuildingMachine> sellHotel(Guest&) override;
    std::unique_ptr<BuildingMachine> mortgage(Guest& owner) override;
    std::unique_ptr<BuildingMachine> relieveMortgage(Guest& owner) override;

//    auto on_event(const HaveAllPropertis&)
//    {
//        return AllPropertisBuildingState(card);
//    }

private:
    const CardInfo& card;
    const District& district;
};
