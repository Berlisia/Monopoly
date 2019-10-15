#include "penalty.h"
#include <iostream>


int Penalty::action() const
{
    std::cout << "Penalty " << std::endl;
    return bonus;
}

unsigned int Penalty::getPossition() const
{
    return possition;
}
