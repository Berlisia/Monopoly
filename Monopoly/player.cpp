#include <vector>
#include <iostream>

#include "player.h"
#include "square.h"

std::vector<Square *> Player::turn()
{
    return move(throwDice());
}

void Player::setNewResult(int newResult)
{
    result = newResult;
}

int Player::getActualResult()
{
    return result;
}

void Player::withdrawMoney(unsigned int )
{
    //int resutAfterWithraw = result - money;
}

void Player::printStatus()
{
    std::cout << name << ": " << result << std::endl;
}

unsigned int Player::throwDice()
{
    return dice.diceThrow();
}

std::vector<Square*> Player::move(unsigned int valueOfSteps)
{
    std::vector<Square*> visitSquares;
    for(auto i = 0; i < valueOfSteps; i++)
    {
        ++actualPossisionOnBoard;
        visitSquares.push_back((*actualPossisionOnBoard).get());
    }
    return visitSquares;
}
