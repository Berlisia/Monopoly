#include "monopolygame.h"
#include "player.h"
#include "die.h"


void MonopolyGame::startGame()
{
    Dice dice;
    Player janek("janek", Piece(board), dice);
    Player krzysiek("krzysiek", Piece(board), dice);

    janek.turn();
    krzysiek.turn();



}
