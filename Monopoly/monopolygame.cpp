#include "monopolygame.h"
#include "player.h"


void MonopolyGame::processActionOnThrought(Player& player)
{
    auto actualSquare = player.moveNextSquare();
    actualSquare->actionOnWalkThrought(player);
}

void MonopolyGame::processActionOnStop(Player& player)
{
    auto actualSquare = player.moveNextSquare();
    actualSquare->actionOnStop(player);
}

void MonopolyGame::processTrun(Player& player)
{
    auto valueOfSteps = player.throwDice();
    for(unsigned int i = 0; i < valueOfSteps - 1; i++)
    {
        processActionOnThrought(player);
    }
    processActionOnStop(player);
    player.printStatus();
}

void MonopolyGame::startGame(unsigned int numberOfTurns)
{
    std::unique_ptr<Player> janek = std::make_unique<Player>("JANEK", board.createBoardIterator());
    std::unique_ptr<Player> krzysiek = std::make_unique<Player>("KRZYSIEK", board.createBoardIterator());

    for(unsigned int i = 0; i < numberOfTurns; i++)
    {
        processTrun(*janek);
        processTrun(*krzysiek);
    }
}
