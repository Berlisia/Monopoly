#include "die.h"

class DiceMock: public Dice
{
public:
    MOCK_METHOD0(diceThrow, unsigned int());
};
