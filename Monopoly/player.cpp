#include "player.h"

void Player::turn()
{
    Squers squaresPath = piece.move(throwDice());

    std::cout << name << ": " << result << endl;
}

void Player::setNewResult(int newResult)
{
    result = newResult;
}

const int Player::getActualResult()
{
    return result;
}

void Player::withdrawMoney(unsigned int money)
{
    //int resutAfterWithraw = result - money;
}

int Player::throwDice()
{
    return dice.diceThrow();
}
