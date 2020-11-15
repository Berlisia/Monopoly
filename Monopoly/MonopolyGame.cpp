#include "MonopolyGame.h"
#include "Player.h"

void MonopolyGame::turn(Contestant& player)
{
    player.turn();
    auto status = player.status();
    status.update();
}

void MonopolyGame::startGame(unsigned int numberOfTurns)
{
    for (unsigned int i = 0; i < numberOfTurns; i++)
    {
        std::cout << "------Turn: " << i + 1 << "------" << std::endl;
        for (auto& player : players)
        {
            turn(*player);
        }
    }
    std::cout << "END OF THE GAME" << std::endl;
}
