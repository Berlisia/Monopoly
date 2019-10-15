#pragma once
#include <vector>
#include "square.h"
#include <memory>

class Board
{
public:
    Board();

    const Square& getSquareFromBoard(const Square& start, int value) const;
    const Square& getStart() const;
private:
    std::vector<std::shared_ptr<Square>> squares;
    const int numberOfSquares = 40;
};
