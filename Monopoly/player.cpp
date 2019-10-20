#include <vector>
#include <iostream>

#include "player.h"
#include "square.h"

Player::Player(std::string p_name, BoardIterator p_boardIterator):
    name(p_name),
    actualPossisionOnBoard(p_boardIterator),
    active(std::make_unique<State>(State{&Player::moveNextSquareInStateActive, &Player::throwDiceInStateActive})),
    inPrisone(std::make_unique<State>(State{&Player::moveNextSquareDefault, &Player::throwDiceInStatePrisone})),
    bancrut(std::make_unique<State>(State{&Player::moveNextSquareDefault, &Player::throwDiceInStateBancrut}))
{
    currentState = active.get();
}

void Player::addMoney(unsigned int money)
{
    result += money;
}

unsigned int Player::withdrawMoney(unsigned int valueToTake)
{
    auto resultBeforeWithdraw = int(result - valueToTake);
    if(resultBeforeWithdraw >= 0)
    {
        result = resultBeforeWithdraw;
        return valueToTake;
    }
    stateTransition(bancrut.get());
    return result;
}

void Player::printStatus()
{
    std::cout << "Result: " << result << std::endl;
}

const std::string &Player::myName()
{
    return name;
}

void Player::stateTransition(State* state)
{
    currentState = state;
}

bool Player::comparePlayer(const Player &player)
{
    return name.compare(player.name);
}

bool Player::wantBuyProperty(unsigned int price)
{
    if(price < result)
    {
        return true;
    }
    return false;
}

void Player::lockInPrison()
{
    numberOfSkipedTurns = 2;
    stateTransition(inPrisone.get());
}

Square* Player::moveNextSquare()
{
    return currentState->moveNextSquare(*this);
}

Square* Player::moveNextSquareInStateActive()
{
    ++actualPossisionOnBoard;
    return (*actualPossisionOnBoard).get();
}

Square* Player::moveNextSquareDefault()
{
    return nullptr;
}

unsigned int Player::throwDice()
{
    std::cout << "Turn " << name << " ";
    return currentState->throwDice(*this);
}

unsigned int Player::throwDiceInStateActive()
{
    return dice.diceThrow();
}

unsigned int Player::throwDiceInStatePrisone()
{
    numberOfSkipedTurns--;
    if(numberOfSkipedTurns == 0)
    {
        stateTransition(active.get());
    }
    return 0;
}

unsigned int Player::throwDiceInStateBancrut()
{
    std::cout << name << " is BUNCRUT" << std::endl;
    return 0;
}

