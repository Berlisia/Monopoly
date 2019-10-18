#include "property.h"
#include "player.h"

void Property::actionOnStop(Player& player)
{
    if(owner)
    {
        payRentByGuest(player);
    }
    else
    {
        bayPropertyByNewOwner(player);
    }
}

void Property::actionOnWalkThrought(Player &)
{
    std::cout << "  Walk throught PROPERTY" <<  std::endl;
}

void Property::payRentByGuest(Player& player)
{
    if(!owner->comparePlayer(player))
    {
        auto money = player.withdrawMoney(rent);
        owner->setNewResult(owner->getActualResult() - money);
    }
}

void Property::bayPropertyByNewOwner(Player& player)
{
    if(player.wantBuyProperty(price))
    {
        player.setNewResult(player.getActualResult() - price);
        owner = &player;
    }
}
