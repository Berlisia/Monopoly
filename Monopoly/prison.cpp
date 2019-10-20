#include "prison.h"
#include "player.h"

void Prisone::actionOnStop(Player& player)
{
    player.lockInPrison();
    std::cout<< " Stop on PRISON" << std::endl;
}

void Prisone::actionOnWalkThrought(Player &)
{
}
