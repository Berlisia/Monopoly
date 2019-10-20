#pragma once
#include <vector>
#include <memory>

#include "state.h"

class StateMachine
{
public:
    virtual ~StateMachine() = default;
protected:
    virtual void stateTransition(State* state) = 0;
    State* currentState;
};
