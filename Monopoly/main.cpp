#include <iostream>
#include <utility>

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
int PRICE_FOR_PENALTY = 50;
int PRICE_FOR_REWARD = 20;
int NUMBER_OF_SQUERS = 40;
}

template<typename T, typename ...Args>
std::unique_ptr<T> createSquare(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

Squers createSimpleBoard()
{
    Squers squares;
    for(int i = 0; i < 1; i++)
    {
        squares.push_back(createSquare<Start>(PRICE_FOR_START));
    }
    for(int i = 1; i < 25; i++)
    {
        squares.push_back(createSquare<Penalty>(PRICE_FOR_PENALTY));
    }
    for(int i = 25; i < NUMBER_OF_SQUERS; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    }
    return squares;
}

int main()
{
    Squers squares = createSimpleBoard();
    Board board(std::move(squares));
    Dice dice;
    MonopolyGame game(std::move(board), dice);
    game.startGame();

    return 0;
}
