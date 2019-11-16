#include <vector>
#include <iostream>
#include <algorithm>

#include "player.h"
#include "Square/square.h"
#include "Square/estate.h"
#include "stateactiveplayer.h"
#include "stateplayerbancrut.h"
#include "stateplayerinprison.h"
#include "die.h"

Player::Player(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice, const SubjectBuildingProperty& p_buildingProperty):
    name(p_name),
    actualPossisionOnBoard(p_boardIterator),
    propertis(p_buildingProperty),
    dice(p_dice)
{
    stateTransition(std::make_unique<StateActivePlayer>());
}

void Player::turn()
{
    std::cout << "Turn " << name << " ";
    currentState->turn(*this);
}

void Player::move()
{
    auto valueOfSteps = rollDice();
    walkThrought(valueOfSteps);
    actionOnStop();
}

void Player::lockInPrison(Squers::iterator prison)
{
    actualPossisionOnBoard.moveToNewCursor(prison);
    stateTransition(std::make_unique<StatePlayerInPrison>());
}

void Player::addMoney(unsigned int moneyToAdd)
{
    money += moneyToAdd;
}

bool Player::buyProperty(unsigned int price, const Estate* property, const District& district)
{
    if(haveEnoughtMoney(price))
    {
        money -= price;
        propertis.addNew(property, district);
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
    if(moneyBeforeWithdraw >= 0)
    {
        money = moneyBeforeWithdraw;
        return true;
    }
    //stateTransition(std::make_unique<StatePlayerBancrut>());
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
    return PlayerStatus {actualPossisionOnBoard, money, propertis.snapchotPropertis()};
}

const std::string &Player::myName()
{
    return name;
}

void Player::stateTransition(std::unique_ptr<State> state)
{
    currentState = std::move(state);
}

void Player::moveNextSquare()
{
    ++actualPossisionOnBoard;
}

Square* Player::actualSquare()
{
    return (*actualPossisionOnBoard).get();
}

void Player::walkThrought(unsigned int valueOfSteps)
{
    moveNextSquare();
    for(unsigned int i = 0; i < valueOfSteps - 1; i++)
    {
        actionOnWalkThrought();
    }
}

void Player::actionOnWalkThrought()
{
    actualSquare()->actionOnWalkThrought(*this);
    moveNextSquare();
}

void Player::actionOnStop()
{
    actualSquare()->actionOnStop(*this);
}

