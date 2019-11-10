#pragma once

#include "guest.h"
#include "playerStatus.h"

class Contestant : public Guest
{
public:
    virtual ~Contestant() = default;
    virtual const PlayerStatus status() = 0;
    virtual void turn() = 0;
};
