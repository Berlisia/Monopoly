#pragma once
#include "square.h"

class Start : public Square
{
public:
    Start(int p_bonus, unsigned int p_possition):
        bonus(p_bonus), possition(p_possition)
    {}

    int action() const override;
    unsigned int getPossition() const override;
private:
    int bonus;
    unsigned int possition;
};
