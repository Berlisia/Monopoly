#pragma once

#include <optional>
#include <variant>

template<typename Derived, typename StateVariant, typename EventVariant>
class FsmBase
{
public:
    using base_type = FsmBase<Derived, StateVariant, EventVariant>;

    void dispatch(EventVariant& event)
    {
        Derived& fsm = static_cast<Derived&>(*this);
        auto onEvent = [&](auto& s, auto& e) -> std::optional<StateVariant> { return fsm.on_event(s, e); };
        auto newState = std::visit(onEvent, state, event);
        if(newState)
        {
            std::visit([&](auto& s){ fsm.on_exit(s); }, state);
            state = *std::move(newState);
            std::visit([&](auto& s){ fsm.on_enter(s); }, state);
        }
    }

    // default implementation of handlers
    template<typename State> void on_enter(State&) {}
    template<typename State> void on_exit(State&) {}
    template<typename State, typename Event>
    std::optional<StateVariant> on_event(State&, Event&) { return std::nullopt; }

private:
    StateVariant state;

};
