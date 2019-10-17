#include <iostream>
#include "square.h"
#include "monopolygame.h"
#include "board.h"
#include "start.h"
#include "reward.h"
#include "penalty.h"

using namespace std;

namespace
{
int PRICE_FOR_START = 100;
int PRICE_FOR_PENALTY = -50;
int PRICE_FOR_REWARD = 20;
int NUMBER_OF_SQUERS = 40;
}

Squers createSimpleBoard()
{
    Squers squares;
    for(int i = 0; i < 10; i++)
    {
        squares.push_back(std::make_shared<Start>(PRICE_FOR_START));
    }
    for(int i = 10; i < 25; i++)
    {
        squares.push_back(std::make_shared<Penalty>(PRICE_FOR_PENALTY));
    }
    for(int i = 25; i < NUMBER_OF_SQUERS; i++)
    {
        squares.push_back(std::make_shared<Reward>(PRICE_FOR_REWARD));
    }
    return squares;
}

int main()
{
    cout << "Hello World!" << endl;

    Squers squares;
    Board board(squares);
    Dice dice;
    MonopolyGame game(board, dice);
    game.startGame();

    return 0;
}
