#pragma once

#include <random>
#include <iostream>

class Dice
{
public:

unsigned int diceThrow() const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist12(1, 12);
    auto number = dist12(rng);
    std::cout << "throw: " << number << std::endl;
    return number;
}

};
