#pragma once
#include <variant>

struct Active
{
};
struct Bancrut
{
};
struct InPrison
{
    unsigned int numberOfSkipedTurns = 2;
};
using PlayerState = std::variant<Active, Bancrut, InPrison>;
