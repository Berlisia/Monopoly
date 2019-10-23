#include "randomsquare.h"
#include "guest.h"

#include <random>

void RandomSquare::actionOnStop(Guest& player)
{
    std::cout << "---RANDOM SQUARE!---" << std::endl;
    squares[randomNumber()]->actionOnStop(player);
}

void RandomSquare::actionOnWalkThrought(Guest& )
{
}

unsigned int RandomSquare::randomNumber()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist12(0, squares.size() - 1);
    return dist12(rng);
}
