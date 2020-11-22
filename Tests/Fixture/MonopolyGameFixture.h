#pragma once
#include "Board.h"
#include "Contestant.h"

class MonopolyGameFixture
{
public:
    void turn(Contestant& player, BoardIterator& possition);

private:
    Square* actualSquare(BoardIterator& possition);
    void walkThrought(Contestant& player, BoardIterator& possition);
    void actionOnStop(Contestant& player, BoardIterator& possition);
};