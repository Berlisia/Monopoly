#include <vector>
#include <iostream>

#include "player.h"
#include "square.h"

void Player::setNewResult(int newResult)
{
    result = newResult;
}

int Player::getActualResult()
{
    return result;
}

unsigned int Player::withdrawMoney(unsigned int valueToTake)
{
    unsigned int money = result - valueToTake;
    if(money > 0)
    {
        result = money;
        return valueToTake;
    }
    isBancrut = true;
    return result;
}

void Player::printStatus()
{
    std::cout << name << ": " << result << std::endl;
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

unsigned int Player::lockInPrison(unsigned int numberfOfTurns)
{
    numberOfSkipedTurns = numberfOfTurns;
}

bool Player::isInPrison()
{
    return numberOfSkipedTurns == 0;
}

Square* Player::moveNextSquare()
{
    ++actualPossisionOnBoard;
    return (*actualPossisionOnBoard).get();
}

unsigned int Player::throwDice()
{
    if(numberOfSkipedTurns == 0)
    {
        return dice.diceThrow();
    }
    numberOfSkipedTurns--;
    return 0;
}

