#include "monopolygame.h"
#include "player.h"

void MonopolyGame::turn(Player& player)
{
    player.turn();
    player.printStatus();
}

void MonopolyGame::startGame(unsigned int numberOfTurns)
{
    for(unsigned int i = 0; i < numberOfTurns; i++)
    {
        std::cout << "------Turn: " << i + 1 << "------" << std::endl;
        for(auto& player: players)
        {
            turn(*player);
        }
    }
    std::cout << "END OF THE GAME" << std::endl;
}
