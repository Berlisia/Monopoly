#include <iostream>
#include <utility>

#include "square.h"
#include "monopolygame.h"
#include "board.h"
#include "start.h"
#include "reward.h"
#include "penalty.h"
#include "deposite.h"
#include "property.h"
#include "randomsquare.h"
#include "board.h"

using namespace std;

namespace
{
int PRICE_FOR_START = 100;
int PRICE_FOR_PENALTY = 50;
int PRICE_FOR_REWARD = 20;
int NUMBER_OF_SQUERS = 40;
unsigned int PRICE_FOR_DEPOSITE = 50;
}

template<typename T, typename ...Args>
std::unique_ptr<T> createSquare(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

void createRandomSquare(Squers& squares)
{
    Squers randomSquares;
    randomSquares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    randomSquares.push_back(createSquare<Penalty>(PRICE_FOR_PENALTY));
    randomSquares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    squares.push_back(createSquare<RandomSquare>(std::move(randomSquares)));
}

Squers createSimpleBoard()
{
    Squers squares;
    for(int i = 0; i < 1; i++)
    {
        squares.push_back(createSquare<Start>(PRICE_FOR_START));
    }
    squares.push_back(createSquare<Property>(100, 20));
    createRandomSquare(squares);
    for(int i = 4; i < 10; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    }
    squares.push_back(createSquare<Property>(100, 20));
    createRandomSquare(squares);
    squares.push_back(createSquare<Deposite>(PRICE_FOR_DEPOSITE));
    for(int i = 13; i < 20; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_DEPOSITE));
    }
    squares.push_back(createSquare<Property>(200, 30));
    createRandomSquare(squares);
    for(int i = 22; i < 30; i++)
    {
        squares.push_back(createSquare<Penalty>(PRICE_FOR_PENALTY));
    }
    squares.push_back(createSquare<Property>(300, 40));
    createRandomSquare(squares);
    for(int i = 32; i < NUMBER_OF_SQUERS; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    }
    return squares;
}

int main()
{
    Squers squares = createSimpleBoard();
    Board board(std::move(squares));
    MonopolyGame game(std::move(board));
    game.startGame(10);

    return 0;
}
