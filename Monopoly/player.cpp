#include <vector>
#include <iostream>

#include "player.h"
#include "Square/square.h"
#include "stateactiveplayer.h"
#include "stateplayerbancrut.h"
#include "stateplayerinprison.h"

Player::Player(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice):
    name(p_name),
    actualPossisionOnBoard(p_boardIterator),
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
    auto valueOfSteps = dice.diceThrow();
    walkThrought(valueOfSteps);
    actionOnStop();
}

void Player::lockInPrison()
{
    stateTransition(std::make_unique<StatePlayerInPrison>());
}

void Player::addMoney(unsigned int moneyToAdd)
{
    money += moneyToAdd;
}

unsigned int Player::withdrawMoney(unsigned int valueToTake)
{
    auto moneyBeforeWithdraw = int(money - valueToTake);
    if(moneyBeforeWithdraw >= 0)
    {
        money = moneyBeforeWithdraw;
        return valueToTake;
    }
    stateTransition(std::make_unique<StatePlayerBancrut>());
    return money;
}

void Player::printStatus()
{
    std::cout << "Result: " << money << std::endl;
}

const std::string &Player::myName()
{
    return name;
}

void Player::stateTransition(std::unique_ptr<State> state)
{
    currentState = std::move(state);
}

bool Player::wantBuyProperty(unsigned int price)
{
    if(price < money)
    {
        return true;
    }
    return false;
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

