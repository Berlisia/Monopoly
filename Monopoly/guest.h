#pragma once
#include <string>

#include "board.h"
#include "Square/district.h"

class Property;
class Estate;

class Guest
{
public:
    virtual ~Guest() = default;

    virtual void lockInPrison(Squers::iterator) = 0;
    virtual bool withdrawMoney(unsigned int money) = 0;
    virtual bool haveEnoughtMoney(unsigned int money) = 0;
    virtual void addMoney(unsigned int money) = 0;
    virtual bool buyProperty(unsigned int price, const Estate* property, const District& district) = 0;
    virtual void sellProperty(unsigned int price, const Estate* property, const District& district) = 0;
    virtual unsigned int checkPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict) = 0;
    virtual unsigned int rollDice() = 0;
    virtual const std::string& myName() = 0;
};
