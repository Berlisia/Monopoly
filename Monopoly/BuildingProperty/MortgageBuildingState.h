#pragma once

#include "BuildingMachine.h"

class District;

class MortgageBuildingState : public BuildingMachine {
public:
  MortgageBuildingState(const District &p_district, const CardInfo &p_card)
      : card(p_card), district(p_district) {}

  Rent calculateRent() const override;

  std::unique_ptr<BuildingMachine> buyHouse(unsigned int numberOfHouse,
                                            Guest &) override;
  std::unique_ptr<BuildingMachine> buyHotel(Guest &) override;
  std::unique_ptr<BuildingMachine> sellHouse(unsigned int numberOfHouse,
                                             Guest &) override;
  std::unique_ptr<BuildingMachine> sellHotel(Guest &) override;
  std::unique_ptr<BuildingMachine> mortgage(Guest &owner) override;
  std::unique_ptr<BuildingMachine> relieveMortgage(Guest &owner) override;

private:
  const CardInfo &card;
  const District &district;
};
