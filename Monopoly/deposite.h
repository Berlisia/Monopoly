#pragma once

#include "square.h"

class Deposite : public Square
{
public:
    Deposite(unsigned int p_valueToStore): valueToStore(p_valueToStore)
    {
    }

    virtual void actionOnStop(Player&) const = 0;
    virtual void actionOnWalkThrought(Player&) const = 0;
private:
    unsigned int valueToStore;
    static unsigned int depositeMoney;
};
