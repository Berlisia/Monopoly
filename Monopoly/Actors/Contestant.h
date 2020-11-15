#pragma once

#include "Guest.h"
#include "PlayerStatus.h"

class Contestant : public Guest {
public:
  virtual ~Contestant() = default;
  virtual const PlayerStatus status() = 0;
  virtual void turn() = 0;
};
