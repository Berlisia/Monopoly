#include "board.h"
#include "start.h"
#include "reward.h"
#include "penalty.h"
#include <algorithm>

namespace
{
int PRICE_FOR_START = 100;
int PRICE_FOR_PENALTY = -50;
int PRICE_FOR_REWARD = 20;
}


Board::Board()
{
    //squares.push_back(std::make_shared<Start>(PRICE_FOR_START, 1));
    for(int i = 0; i < 10; i++)
    {
        squares.push_back(std::make_shared<Start>(PRICE_FOR_START, i+1));
    }
    for(int i = 10; i < 25; i++)
    {
        squares.push_back(std::make_shared<Penalty>(PRICE_FOR_PENALTY, i+1));
    }
    for(int i = 25; i < numberOfSquares; i++)
    {
        squares.push_back(std::make_shared<Reward>(PRICE_FOR_REWARD, i+1));
    }
}

const Square& Board::getSquareFromBoard(const Square& start, int value) const
{
    unsigned int possition = (start.getPossition() + value) % numberOfSquares;
    return *squares[possition - 1];
}

//const std::vector<const Square&> getPath(const Square& start, int value)
//{

//}

const Square &Board::getStart() const
{
    return *squares[0];
}
