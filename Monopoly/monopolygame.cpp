#include "monopolygame.h"
#include "player.h"

void MonopolyGame::turn(Player& player)
{
    player.turn();
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
