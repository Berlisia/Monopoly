#include "monopolygame.h"
#include "player.h"


void MonopolyGame::processActionOnThrought(Player& player)
{
    auto actualSquare = player.moveNextSquare();
    if(actualSquare)
        actualSquare->actionOnWalkThrought(player);
}

void MonopolyGame::processActionOnStop(Player& player)
{
    auto actualSquare = player.moveNextSquare();
    if(actualSquare)
        actualSquare->actionOnStop(player);
}

void MonopolyGame::processTurn(Player& player, unsigned int valueOfSteps)
{
    for(unsigned int i = 0; i < valueOfSteps - 1; i++)
    {
        processActionOnThrought(player);
    }
    processActionOnStop(player);
}

void MonopolyGame::turn(Player& player)
{
    auto valueOfSteps = player.throwDice();
    if(valueOfSteps != 0)
    {
        processTurn(player, valueOfSteps);
    }
    player.printStatus();
}

void MonopolyGame::startGame(unsigned int numberOfTurns)
{
    std::unique_ptr<Player> janek = std::make_unique<Player>("JANEK", board.createBoardIterator());
    std::unique_ptr<Player> krzysiek = std::make_unique<Player>("KRZYSIEK", board.createBoardIterator());

    for(unsigned int i = 0; i < numberOfTurns; i++)
    {
        std::cout << "------Turn: " << i + 1 << "------" << std::endl;
        turn(*janek);
        turn(*krzysiek);
    }

    std::cout << "END OF THE GAME" << std::endl;
}
