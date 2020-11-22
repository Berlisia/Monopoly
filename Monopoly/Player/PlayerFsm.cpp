#include "PlayerFsm.h"

void PlayerFsm::dispatch(PlayerEvent& event)
{
    auto& fsm = *this;
    auto onEvent = [&](auto& s, auto& e) -> std::optional<PlayerState> { return fsm.on_event(s, e); };
    auto newState = std::visit(onEvent, state, event);
    if (newState)
    {
        std::visit([&](auto& s) { fsm.on_exit(s); }, state);
        state = *std::move(newState);
        std::visit([&](auto& s) { fsm.on_enter(s); }, state);
    }
}

std::optional<PlayerState> PlayerFsm::on_event(Active&, LockInPrison&)
{
    return InPrison{};
}

std::optional<PlayerState> PlayerFsm::on_event(Active&, IsBancrut&)
{
    return Bancrut{};
}

std::optional<PlayerState> PlayerFsm::on_event(InPrison& state, Turn&)
{
    state.numberOfSkipedTurns--;
    if (state.numberOfSkipedTurns == 0)
    {
        return Active{};
    }
    return std::nullopt;
}

std::optional<PlayerState> PlayerFsm::on_event(InPrison&, IsBancrut&)
{
    return Bancrut{};
}
