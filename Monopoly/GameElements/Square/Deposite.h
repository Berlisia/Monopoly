#pragma once

#include "Square.h"

const std::string DEPOSITE_NAME = "DEPOSITE";

class Deposite : public Square
{
public:
    Deposite(unsigned int p_valueToStore) : valueToStore(p_valueToStore), depositeMoney(0) {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

private:
    unsigned int valueToStore;
    unsigned int depositeMoney;
};
