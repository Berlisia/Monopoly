#pragma once
#include <memory>
#include <vector>

#include "State.h"

class StateMachine
{
public:
    virtual ~StateMachine() = default;
    virtual void stateTransition(std::unique_ptr<State> state) = 0;

protected:
    std::unique_ptr<State> currentState;
};
