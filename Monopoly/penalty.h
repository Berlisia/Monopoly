#pragma once
#include "square.h"

class Penalty : public Square
{
public:
    Penalty(int p_bonus, unsigned int p_possition):
        bonus(p_bonus), possition(p_possition)
    {}

    int action() const override;
    unsigned int getPossition() const override;
private:
    int bonus;
    unsigned int possition;
};
