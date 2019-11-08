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
    dice(p_dice),
    buildingProperty(p_buildingProperty)
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
    if(price < money)
    {
        std::cout << "BUY prop" << std::endl;
        money -= price;
        propertis.push_back(property);
        notifyBuildingProperty(district);
        return true;
    }
    return false;
}

std::vector<const Estate*>::iterator Player::findInPropertis(const Estate* property)
{
    return std::find_if(propertis.begin(), propertis.end(),
                        [property](const Estate* playerProperty){return *property == *playerProperty;});
}

unsigned int Player::checkPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict)
{
    unsigned int countPropertisFromDistrict = 0;
    for(const auto districtProperty: propertisInDistrict)
    {
        auto it = findInPropertis(districtProperty);
        if(it != propertis.end())
            countPropertisFromDistrict++;
    }
    return countPropertisFromDistrict;
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

void Player::printStatus()
{
    std::cout << "Result: " << money << std::endl;
}

const PlayerStatus Player::status()
{
    return PlayerStatus {actualPossisionOnBoard, money, propertis};
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

void Player::notifyBuildingProperty(const District& district)
{
    auto allPropertis = checkPropertisInDistrict(district.propertis());
    if(allPropertis == district.propertis().size())
    {
        buildingProperty.notifyForHaveAllPropertis(district);
        return;
    }
    buildingProperty.notifyForNotAllPropertis(district);
}

