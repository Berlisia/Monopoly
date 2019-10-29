#pragma once
#include <string>

#include "board.h"

class Property;
class Estate;

class Guest
{
public:
    virtual ~Guest() = default;

    virtual void lockInPrison(Squers::iterator) = 0;
    virtual unsigned int withdrawMoney(unsigned int money) = 0;
    virtual void addMoney(unsigned int money) = 0;
    virtual bool buyProperty(unsigned int price, Estate* property) = 0;
    virtual unsigned int checkPropertisInDistrict(const std::vector<Estate*>& propertisInDistrict) = 0;
    virtual unsigned int rollDice() = 0;
    virtual const std::string& myName() = 0;
};
