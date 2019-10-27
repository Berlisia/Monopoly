#include "start.h"
#include "guest.h"

#include <iostream>

void Start::actionOnStop(Guest& player)
{
    player.addMoney(bonus);
}

void Start::actionOnWalkThrought(Guest& player)
{
    player.addMoney(bonus);
}

const std::string Start::squareName()
{
    return START_NAME;
}
