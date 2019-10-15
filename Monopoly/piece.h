#pragma once
#include "board.h"
#include <memory>

class Piece
{
public:
    Piece(const Board & p_board): board(p_board),
                                  possision(board.getStart())
    {
    }

    const Square& move(int value)
    {
        return board.getSquareFromBoard(possision, value);
    }
private:
    const Board & board;
    const Square& possision;
};
