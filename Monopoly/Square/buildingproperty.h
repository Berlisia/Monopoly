#pragma once
#include <map>

#include "rentpaymode.h"
#include "district.h"
#include "housedevelop.h"
#include "buildingMachine.h"

#include "defultbuildingstate.h"

class BuildingProperty: public RentPayMode, public HouseDevelop
{
public:
    BuildingProperty(const CardInfo p_card, const District& p_district):
        card(p_card),
        district(p_district),
        currentState(std::make_unique<DefaultBuildingState>(card.rent)) {}

    void payRent(Guest& player, Guest& owner) const override;

    void buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    void buyHotel(Guest& owner) override;
    void sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    void sellHotel(Guest& owner) override;

private:
    const CardInfo card;
    const District& district;

    std::unique_ptr<BuildingMachine> currentState;

    void withdrawRent(Rent rent, Guest &player, Guest &owner) const;
    bool haveAllPropertisFromDistrict(Guest& owner) const;
};
