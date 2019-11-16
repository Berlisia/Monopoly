#pragma once
#include <map>

#include "Square/rentpaymode.h"
#include "Square/district.h"
#include "housedevelop.h"
#include "BuildingObserver.h"
#include "BuildingPropertyFsm.h"

class BuildingProperty: public RentPayMode,
                        public HouseDevelop,
                        public BuildingObserver
{
public:
    BuildingProperty(const CardInfo& p_card, const District& p_district):
        card(p_card),
        district(p_district),
        fsm(card, owner, district) {}

    void payRent(Guest& player) override;
    void setNewOwner(Guest& owner) override;

    void buyHouse(unsigned int numberOfHouse, Guest& owner) override;
    void buyHotel(Guest& owner) override;
    void sellHouse(unsigned int numberOfHouse, Guest& owner) override;
    void sellHotel(Guest& owner) override;
    void mortgage(Guest& owner) override;
    void relieveMortgage(Guest& owner) override;

    void updateForAllPropertis() override;
    void updateForNotAllPropertis() override;
    const District& getDistrict() override;

private:
    const CardInfo card;
    const District& district;
    Guest* owner = nullptr;
    BuildingPropertyFsm fsm;

    void withdrawRent(Rent rent, Guest &player) const;
};
