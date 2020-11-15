#include "BlackHole.h"
#include "Guest.h"

void BlackHole::actionOnStop(Guest &) {
  if (isActive) {
    isActive = false;
  } else {
  }
}

void BlackHole::actionOnWalkThrought(Guest &) {}

const std::string BlackHole::squareName() { return BLACK_HOLE_NAME; }
