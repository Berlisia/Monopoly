#pragma once

#include "square.h"

class Deposite : public Square
{
public:
    Deposite(unsigned int p_valueToStore):
        valueToStore(p_valueToStore),
        depositeMoney(0)
    {
    }

    virtual void actionOnStop(Player&);
    virtual void actionOnWalkThrought(Player&);
private:
    unsigned int valueToStore;
    unsigned int depositeMoney;
};
