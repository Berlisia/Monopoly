#pragma once

#include <optional>
#include <variant>

template <typename StateVariant, typename EventVariant>
class FsmBase
{
public:
    using base_type = FsmBase<StateVariant, EventVariant>;
    virtual ~FsmBase() = default;

    virtual void dispatch(EventVariant& event) = 0;

    // default implementation of handlers
    template <typename State>
    void on_enter(State&)
    {
    }
    template <typename State>
    void on_exit(State&)
    {
    }
    template <typename State, typename Event>
    std::optional<StateVariant> on_event(State&, Event&)
    {
        return std::nullopt;
    }

protected:
    StateVariant state;
};
