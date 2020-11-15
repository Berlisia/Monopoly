#pragma once
#include <utility>

#include "BuildingMachine.h"
#include "District.h"

#include "EventVariant.h"
#include "FsmVariant.h"
#include "StateVariant.h"

class BuildingPropertyFsm : public FsmBase<StateBuilding, Event> {
public:
  using FsmBase::on_enter;
  using FsmBase::on_event;
  using FsmBase::on_exit;

  BuildingPropertyFsm(const CardInfo &p_card, const District &p_district)
      : card(p_card), district(p_district) {}

  void dispatch(Event &event) override;

private:
  const CardInfo &card;
  const District &district;
  Guest *owner;

  void on_enter(WithoutOwner &state);
  std::optional<StateBuilding> on_event(WithoutOwner &state, NewOwner &event);

  std::optional<StateBuilding> on_event(Default &, PayRent &);
  std::optional<StateBuilding> on_event(Default &, GetMortgage &);
  std::optional<StateBuilding> on_event(Default &, HaveAllPropertis &);
  std::optional<StateBuilding> on_event(Default &, NewOwner &);
  std::optional<StateBuilding> on_event(Default &, SellToBank &);

  std::optional<StateBuilding> on_event(AllPropertis &, PayRent &);
  std::optional<StateBuilding> on_event(AllPropertis &, BuyHause &);
  std::optional<StateBuilding> on_event(AllPropertis &, GetMortgage &);
  std::optional<StateBuilding> on_event(AllPropertis &, HaveNotAllPropertis &);
  std::optional<StateBuilding> on_event(AllPropertis &, NewOwner &);
  std::optional<StateBuilding> on_event(AllPropertis &, SellToBank &);

  void on_enter(HouseBuilding &);
  std::optional<StateBuilding> on_event(HouseBuilding &, PayRent &);
  std::optional<StateBuilding> on_event(HouseBuilding &, BuyHause &);
  std::optional<StateBuilding> on_event(HouseBuilding &, SellHouse &);
  std::optional<StateBuilding> on_event(HouseBuilding &, BuyHotel &);
  std::optional<StateBuilding> on_event(HouseBuilding &, GetMortgage &);
  std::optional<StateBuilding> on_event(HouseBuilding &, NewOwner &);
  std::optional<StateBuilding> on_event(HouseBuilding &, SellToBank &);
  std::optional<StateBuilding> on_event(HouseBuilding &, HaveNotAllPropertis &);
  void on_exit(HouseBuilding &);

  void on_enter(HotelBuilding &);
  std::optional<StateBuilding> on_event(HotelBuilding &, PayRent &);
  std::optional<StateBuilding> on_event(HotelBuilding &, SellHotel &);
  std::optional<StateBuilding> on_event(HotelBuilding &, GetMortgage &);
  std::optional<StateBuilding> on_event(HotelBuilding &, NewOwner &);
  std::optional<StateBuilding> on_event(HotelBuilding &, SellToBank &);
  std::optional<StateBuilding> on_event(HotelBuilding &, HaveNotAllPropertis &);
  // void on_exit(HotelBuilding&);

  std::optional<StateBuilding> on_event(Mortgage &, NewOwner &);
  std::optional<StateBuilding> on_event(Mortgage &, RelieveMortgage &);
  std::optional<StateBuilding> on_event(Mortgage &, HaveAllPropertis &);

  void buyHouses(HouseBuilding &state, unsigned int numHousesToBuy);
  void sellSomeHouses(HouseBuilding &state, unsigned int houses);
  void sellAllHouses(HouseBuilding &state);
  void sellAllFromHotel();
};
