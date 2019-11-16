#pragma once
#include <utility>

#include "Square/district.h"
#include "buildingMachine.h"

#include "FsmVariant.h"
#include "StateVariant.h"
#include "EventVariant.h"

class BuildingPropertyFsm: public FsmBase<BuildingPropertyFsm, StateBuilding, Event>
{
public:
    using FsmBase::on_event;
    using FsmBase::on_exit;
    using FsmBase::on_enter;

    BuildingPropertyFsm(const CardInfo& p_card, Guest* p_owner, const District& p_district):
        card(p_card),
        district(p_district),
        owner(p_owner) {}

    void on_enter(WithoutOwner& state);
    std::optional<StateBuilding> on_event(WithoutOwner& state, NewOwner& event);

    std::optional<StateBuilding> on_event(Default&, PayRent&);
    std::optional<StateBuilding> on_event(Default&, GetMortgage&);
    std::optional<StateBuilding> on_event(Default&, HaveAllPropertis&);
    std::optional<StateBuilding> on_event(Default&, NewOwner& event);

    std::optional<StateBuilding> on_event(AllPropertis&, PayRent&);
    std::optional<StateBuilding> on_event(AllPropertis&, BuyHause&);
    std::optional<StateBuilding> on_event(AllPropertis&, GetMortgage&);
    std::optional<StateBuilding> on_event(AllPropertis&, HaveNotAllPropertis&);
    std::optional<StateBuilding> on_event(AllPropertis&, NewOwner& event);

    void on_enter(HouseBuilding&);
    std::optional<StateBuilding> on_event(HouseBuilding&, PayRent&);
    std::optional<StateBuilding> on_event(HouseBuilding&, BuyHause&);
    std::optional<StateBuilding> on_event(HouseBuilding&, SellHouse&);
    std::optional<StateBuilding> on_event(HouseBuilding&, BuyHotel&);
    std::optional<StateBuilding> on_event(HouseBuilding&, GetMortgage&);

    void on_enter(HotelBuilding&);
    std::optional<StateBuilding> on_event(HotelBuilding&, PayRent&);
    std::optional<StateBuilding> on_event(HotelBuilding&, SellHotel&);
    std::optional<StateBuilding> on_event(HotelBuilding&, GetMortgage&);

    std::optional<StateBuilding> on_event(Mortgage&, RelieveMortgage&);

private:
    const CardInfo& card;
    const District& district;
    Guest* owner;

    void buyHouses(HouseBuilding& state, unsigned int numHousesToBuy);
    void sellSomeHouses(HouseBuilding& state, unsigned int houses);
    void sellAllHouses(HouseBuilding& state);
};
