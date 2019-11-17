#include <memory>
#include <utility>

#include "buildingproperty.h"
#include "guest.h"
#include "EventVariant.h"
#include "StateVariant.h"

void BuildingProperty::payRent(Guest& player)
{
    Event rentEvent = PayRent{0};
    fsm->dispatch(rentEvent);
    auto rent = std::get<PayRent>(rentEvent).rentToPay;
    withdrawRent(rent, player);
}

void BuildingProperty::setNewOwner(Guest& newOwner)
{
    owner = &newOwner;
    Event eventOwner;
    if(newOwner.myName() == "Bankier") {
        eventOwner = SellToBank{};
    }
    eventOwner = NewOwner{owner};
    fsm->dispatch(eventOwner);
}

void BuildingProperty::buyHouse(unsigned int numberOfNewHouses, Guest&)
{
    Event buyHouseE = BuyHause{numberOfNewHouses};
    fsm->dispatch(buyHouseE);
}

void BuildingProperty::buyHotel(Guest& )
{
    Event buyHotelE = BuyHotel{};
    fsm->dispatch(buyHotelE);
}

void BuildingProperty::sellHouse(unsigned int numberOfHouse, Guest &)
{
    Event sellHouseE = SellHouse{numberOfHouse};
    fsm->dispatch(sellHouseE);
}

void BuildingProperty::sellHotel(Guest& )
{
    Event sellHotelE = SellHotel{};
    fsm->dispatch(sellHotelE);
}

void BuildingProperty::mortgage(Guest &)
{
    Event mortgageE = GetMortgage{};
    fsm->dispatch(mortgageE);
}

void BuildingProperty::relieveMortgage(Guest &)
{
    Event relieveMortgageE = RelieveMortgage{};
    fsm->dispatch(relieveMortgageE);
}

void BuildingProperty::updateForAllPropertis()
{
    Event allPropertis = HaveAllPropertis{};
    fsm->dispatch(allPropertis);
}

void BuildingProperty::updateForNotAllPropertis()
{
    Event notAllPropertis = HaveNotAllPropertis{};
    fsm->dispatch(notAllPropertis);
}

const District &BuildingProperty::getDistrict()
{
    return district;
}

void BuildingProperty::withdrawRent(Rent newRent, Guest &player) const
{
    if(player.withdrawMoney(newRent)) //TODO bancrut
    {
        owner->addMoney(newRent);
    }
}
