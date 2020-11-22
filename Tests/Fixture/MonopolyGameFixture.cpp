#include "MonopolyGameFixture.h"

void MonopolyGameFixture::turn(Contestant& player, BoardIterator& possition)
{
    walkThrought(player, possition);
    actionOnStop(player, possition);
}

Square* MonopolyGameFixture::actualSquare(BoardIterator& possition)
{
    return (*possition).get();
}

void MonopolyGameFixture::walkThrought(Contestant& player, BoardIterator& possition)
{
    unsigned int valueOfSteps = player.rollDice();
    ++possition;
    for (unsigned int i = 0; i < valueOfSteps - 1; i++)
    {
        actualSquare(possition)->actionOnWalkThrought(player);
        ++possition;
    }
}

void MonopolyGameFixture::actionOnStop(Contestant& player, BoardIterator& possition)
{
    actualSquare(possition)->actionOnStop(player);
}