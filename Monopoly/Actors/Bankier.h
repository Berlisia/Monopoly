#pragma once
#include <string>

#include "Guest.h"

class Bankier : public Guest
{
public:
    void lockInPrison();
    bool withdrawMoney(unsigned int money);
    void addMoney(unsigned int money);
    bool haveEnoughtMoney(unsigned int money);
    bool buyProperty(unsigned int price, const Estate* property, const District& district);
    void sellProperty(unsigned int price, const Estate* property, const District& district);
    unsigned int checkPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict);
    unsigned int rollDice();
    const std::string& myName();
};
