#include "monopolygame.h"
#include "player.h"


void MonopolyGame::startGame()
{
    Player janek("janek", Piece(board.createBoardIteratorWithStartPossition()), dice);
    Player krzysiek("krzysiek", Piece(board.createBoardIteratorWithStartPossition()), dice);

    janek.turn();
    krzysiek.turn();
}
