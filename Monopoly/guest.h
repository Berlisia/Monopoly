#pragma once
#include <string>

#include "board.h"

class Guest
{
public:
    virtual ~Guest() = default;

    virtual void lockInPrison(Squers::iterator) = 0;
    virtual unsigned int withdrawMoney(unsigned int money) = 0;
    virtual void addMoney(unsigned int money) = 0;
    virtual bool wantBuyProperty(unsigned int price) = 0;
    virtual const std::string& myName() = 0;
};
