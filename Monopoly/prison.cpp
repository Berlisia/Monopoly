#include "prison.h"
#include "player.h"

void Prisone::actionOnStop(Player& player)
{
    if(!player.isInPrison())
    {
        player.lockInPrison(numberfOfTurns);
    }
}

void Prisone::actionOnWalkThrought(Player &)
{

}
