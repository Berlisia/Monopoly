#pragma once

#include "Square.h"

const std::string PRISON_NAME = "PRISON";

class Prison : public Square
{
public:
    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;
};
