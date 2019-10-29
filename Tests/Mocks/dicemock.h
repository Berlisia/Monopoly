#pragma once
#include <gmock/gmock.h>

#include "die.h"

class DiceMock: public Dice
{
public:
    MOCK_CONST_METHOD0(diceThrow, unsigned int());
};
