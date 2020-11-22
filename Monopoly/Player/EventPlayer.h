#pragma once
#include <variant>

struct Turn
{
};
struct LockInPrison
{
};
struct IsBancrut
{
};
using PlayerEvent = std::variant<Turn, LockInPrison, IsBancrut>;