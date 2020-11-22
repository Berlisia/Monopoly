#include "MonopolyGame.h"
#include "Player.h"

void MonopolyGame::startGame(unsigned int numberOfTurns)
{
    for (unsigned int i = 0; i < numberOfTurns; i++)
    {
        std::cout << "------Turn: " << i + 1 << "------" << std::endl;
        for (auto& player : players)
        {
            walkThrought(*(player.first), player.second);
            actionOnStop(*(player.first), player.second);

            auto status = player.first->status();
            status.update(player.second);
        }
    }
    std::cout << "END OF THE GAME" << std::endl;
}

Square* MonopolyGame::actualSquare(BoardIterator& possition)
{
    return (*possition).get();
}

void MonopolyGame::walkThrought(Contestant& player, BoardIterator& possition)
{
    unsigned int valueOfSteps = player.rollDice();
    ++possition;
    for (unsigned int i = 0; i < valueOfSteps - 1; i++)
    {
        actualSquare(possition)->actionOnWalkThrought(player);
        ++possition;
    }
}

void MonopolyGame::actionOnStop(Contestant& player, BoardIterator& possition)
{
    actualSquare(possition)->actionOnStop(player);
}
