#pragma once
#include <functional>

class Square;
class Player;
struct State
{
    std::function<Square*(Player&)> moveNextSquare;
    std::function<unsigned int(Player&)> throwDice;
};
