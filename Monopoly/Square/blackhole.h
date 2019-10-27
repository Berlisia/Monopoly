#pragma once
#include <memory>

#include "square.h"

const std::string BLACK_HOLE_NAME = "BLACK HOLE";

class BlackHole: public Square
{
public:
    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

private:
    bool isActive = false;
    std::unique_ptr<Square> square;
};
