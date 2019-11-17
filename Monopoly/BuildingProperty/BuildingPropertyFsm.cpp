#include <math.h>

#include "BuildingPropertyFsm.h"

namespace{
constexpr unsigned int MAX_NUMBER_OF_HOUSES = 4;
constexpr unsigned int HOTEL = 5;
}

void BuildingPropertyFsm::dispatch(Event &event)
{
    auto& fsm = *this;
    auto onEvent = [&](auto& s, auto& e) -> std::optional<StateBuilding> { return fsm.on_event(s, e); };
    auto newState = std::visit(onEvent, state, event);
    if(newState)
    {
        state = *std::move(newState);
        std::visit([&](auto& s){ fsm.on_enter(s); }, state);
    }
}

void BuildingPropertyFsm::on_enter(WithoutOwner&)
{
    owner = nullptr;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(WithoutOwner&, NewOwner& event)
{
    owner = event.owner;
    return Default{};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(Default&, PayRent& event)
{
    event.rentToPay = card.rent;
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(Default&, GetMortgage&)
{
    owner->addMoney(card.mortgagePrice);
    return Mortgage{};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(Default &, HaveAllPropertis &)
{
    return AllPropertis{};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(Default &, NewOwner &event)
{
    owner = event.owner;
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(AllPropertis &, PayRent& event)
{
    event.rentToPay = card.rent * 2;
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(AllPropertis &, BuyHause& event)
{
    if(event.numHousesToBuy <= MAX_NUMBER_OF_HOUSES){
        return HouseBuilding{event.numHousesToBuy};
    }
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(AllPropertis&, GetMortgage&)
{
    owner->addMoney(card.mortgagePrice);
    return Mortgage{};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(AllPropertis&, HaveNotAllPropertis&)
{
    return Default{};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(AllPropertis &, NewOwner &event)
{
    owner = event.owner;
    return Default{};
}

void BuildingPropertyFsm::on_enter(HouseBuilding& state)
{
    owner->withdrawMoney(state.numberOfHouses * card.housePrice);
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HouseBuilding& state, PayRent &event)
{
    event.rentToPay = card.buildingRent.at(state.numberOfHouses);
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HouseBuilding& state, BuyHause &event)
{
    buyHouses(state, event.numHousesToBuy);
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HouseBuilding& state, SellHouse& event)
{
    unsigned int housesAfterSell = state.numberOfHouses - event.numHousesToSell;
    if(housesAfterSell == 0){
        sellAllHouses(state);
        return AllPropertis{};
    }

    if(state.numberOfHouses > event.numHousesToSell){
        sellSomeHouses(state, event.numHousesToSell);
    }
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HouseBuilding& state, BuyHotel&)
{
    if(state.numberOfHouses == MAX_NUMBER_OF_HOUSES){
        return HotelBuilding{};
    }
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HouseBuilding& state, GetMortgage &)
{
    sellAllHouses(state);
    owner->addMoney(card.mortgagePrice);
    return Mortgage{};
}

void BuildingPropertyFsm::on_enter(HotelBuilding &)
{
    owner->withdrawMoney(card.hotelPrice);
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HotelBuilding&, PayRent& event)
{
    event.rentToPay = card.buildingRent.at(HOTEL);
    return std::nullopt;
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HotelBuilding&, SellHotel&)
{//TODO sell hotel and get 4 houses or sell all?
    owner->addMoney(card.hotelPrice / 2);
    owner->addMoney(card.housePrice * 4);
    return HouseBuilding{MAX_NUMBER_OF_HOUSES};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(HotelBuilding &, GetMortgage &)
{
    owner->addMoney(card.hotelPrice/2);
    owner->addMoney(card.housePrice/2 * MAX_NUMBER_OF_HOUSES);
    return Mortgage{};
}

std::optional<StateBuilding> BuildingPropertyFsm::on_event(Mortgage &, RelieveMortgage &)
{
    auto mortgage = static_cast<unsigned int>(std::round(card.mortgagePrice * 1.1));
    if(owner->withdrawMoney(mortgage)){
        if(owner->checkPropertisInDistrict(district.propertis()) == district.propertis().size()){
            return AllPropertis{};
        }
        return Default{};
    }
    return std::nullopt;
}

void BuildingPropertyFsm::buyHouses(HouseBuilding& state, unsigned int numHousesToBuy)
{
    auto numberOfHausesAfterAdd = state.numberOfHouses + numHousesToBuy;
    if(state.numberOfHouses <= MAX_NUMBER_OF_HOUSES and numberOfHausesAfterAdd <= MAX_NUMBER_OF_HOUSES){
        owner->withdrawMoney(numHousesToBuy * card.housePrice);
        state.numberOfHouses = numberOfHausesAfterAdd;
    }
}

void BuildingPropertyFsm::sellSomeHouses(HouseBuilding& state, unsigned int houses)
{
    owner->addMoney(houses * card.housePrice/2);
    state.numberOfHouses -= houses;
}

void BuildingPropertyFsm::sellAllHouses(HouseBuilding& state)
{
    owner->addMoney(state.numberOfHouses * card.housePrice/2);
}
