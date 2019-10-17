#include "monopolygame.h"
#include "player.h"

void MonopolyGame::processTrun(Player& player)
{
    auto squarePath = player.turn();
    for(unsigned int i = 0; i < squarePath.size() - 1; i++)
    {
        squarePath[i]->actionOnWalkThrought(player);
    }
    squarePath[squarePath.size() - 1]->actionOnStop(player);
    player.printStatus();
}

void MonopolyGame::startGame()
{
    Player janek("janek", dice, board.createBoardIterator());
    Player krzysiek("krzysiek", dice, board.createBoardIterator());

    processTrun(janek);
    processTrun(krzysiek);
}
