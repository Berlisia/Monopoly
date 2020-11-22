#pragma once

#include "EventPlayer.h"
#include "FsmVariant.h"
#include "StatePlayer.h"

class PlayerFsm : public FsmBase<PlayerState, PlayerEvent>
{
public:
    using FsmBase::on_enter;
    using FsmBase::on_event;
    using FsmBase::on_exit;

    void dispatch(PlayerEvent& event) override;

private:
    std::optional<PlayerState> on_event(Active&, LockInPrison&);
    std::optional<PlayerState> on_event(Active&, IsBancrut&);

    std::optional<PlayerState> on_event(InPrison&, Turn&);
    std::optional<PlayerState> on_event(InPrison&, IsBancrut&);
};