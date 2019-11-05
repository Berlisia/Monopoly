#pragma once
#include <memory>

class HouseDevelop;

class BuildingState
{
public:
    virtual ~StateMachine() = default;
    virtual void stateTransition(std::unique_ptr<HouseDevelop> state) = 0;

};
