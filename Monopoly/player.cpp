#include <vector>
#include <iostream>

#include "player.h"
#include "Square/square.h"
#include "stateactiveplayer.h"
#include "stateplayerbancrut.h"
#include "stateplayerinprison.h"

Player::Player(std::string p_name, BoardIterator p_boardIterator):
    name(p_name),
    actualPossisionOnBoard(p_boardIterator)
{
    stateTransition(std::make_unique<StateActivePlayer>());
}

void Player::turn()
{
    currentState->turn(*this);
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

bool Player::comparePlayer(const Player &player)
{
    return name.compare(player.name);
}

bool Player::wantBuyProperty(unsigned int price)
{
    if(price < money)
    {
        return true;
    }
    return false;
}

void Player::lockInPrison()
{
    stateTransition(std::make_unique<StatePlayerInPrison>());
}

void Player::moveOn(unsigned int valueOfSteps)
{
    auto actualSquare = moveNextSquare();
    for(unsigned int i = 0; i < valueOfSteps - 1; i++)
    {
        actualSquare->actionOnWalkThrought(*this);
        actualSquare = moveNextSquare();
    }
    actualSquare->actionOnStop(*this);
}

Square* Player::moveNextSquare()
{
    ++actualPossisionOnBoard;
    return (*actualPossisionOnBoard).get();
}

unsigned int Player::throwDice()
{
    std::cout << "Turn " << name << " ";
    return dice.diceThrow();
}

