#pragma once

#include "Board.h"
#include "Square.h"

const std::string GO_TO_PRISON_NAME = "BLACK HOLE";

class GoToPrison : public Square
{
public:
    GoToPrison(Squers::iterator p_prisonOnBoard) : prisonPossisionOnBoard(p_prisonOnBoard) {}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

private:
    Squers::iterator prisonPossisionOnBoard;
};
