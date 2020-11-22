#include <algorithm>
#include <iostream>
#include <vector>

#include "Die.h"
#include "Estate.h"
#include "Player.h"
#include "Square.h"

Player::Player(std::string p_name, const Dice& p_dice, const SubjectBuildingProperty& p_buildingProperty) :
    name(p_name), propertis(p_buildingProperty), fsm(std::make_unique<PlayerFsm>()), dice(p_dice)
{
}

void Player::turn()
{
    std::cout << "Turn " << name << " ";
    // turn()
}

void Player::lockInPrison()
{
    // actualPossisionOnBoard.moveToNewCursor(prison); TODO prison possition !!!
    PlayerEvent lockEvent = LockInPrison{};
    fsm->dispatch(lockEvent);
}

void Player::addMoney(unsigned int moneyToAdd)
{
    money += moneyToAdd;
    std::cout << name << " Add " << moneyToAdd << " after: " << money << std::endl;
}

bool Player::buyProperty(unsigned int price, const Estate* property, const District& district)
{
    if (haveEnoughtMoney(price))
    {
        money -= price;
        propertis.addNew(property, district);
        std::cout << name << " Buy: " << property->estateName() << " money " << money << std::endl;
        return true;
    }
    return false;
}

void Player::sellProperty(unsigned int price, const Estate* property, const District& district)
{
    money += price;
    propertis.remove(property, district);
}

unsigned int Player::checkPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict)
{
    return propertis.countPropertisInDistrict(propertisInDistrict);
}

unsigned int Player::rollDice()
{
    return dice.diceThrow();
}

bool Player::withdrawMoney(unsigned int valueToTake)
{
    auto moneyBeforeWithdraw = int(money - valueToTake);
    if (moneyBeforeWithdraw >= 0)
    {
        money = moneyBeforeWithdraw;
        std::cout << name << " withraw money " << valueToTake << " after: " << money << std::endl;
        return true;
    }
    // stateTransition(std::make_unique<StatePlayerBancrut>());
    return false;
}

bool Player::haveEnoughtMoney(unsigned int price)
{
    return price < money;
}

void Player::printStatus()
{
    std::cout << "Result: " << money << std::endl;
}

const PlayerStatus Player::status()
{
    return PlayerStatus{money, propertis.snapchotPropertis()};
}

const std::string& Player::myName()
{
    return name;
}
