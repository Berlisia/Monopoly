#include "start.h"
#include <iostream>

int Start::action() const
{
    std::cout << "Start action!" << std::endl;
    return bonus;

}

unsigned int Start::getPossition() const
{
    return possition;
}
