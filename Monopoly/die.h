#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Dice
{
public:

    int diceThrow() const
    {
        srand((unsigned)time(0));
        int i;
        i = (rand()%12)+1;
        cout << "throw: " << i << endl;
        return i;
    }

};
