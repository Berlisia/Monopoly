#pragma once
#include <map>
#include <vector>

#include "player.h"
#include "Square/property.h"

typedef std::map<Player*, std::vector<Property*>> Register;

class Bank
{
public:
    Bank()
    {
    }
private:
    Register registry;
};
