//
// Created by neodima on 10.06.24.
//

#pragma once

#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23 {

struct Keplerian {
  scalar semiMajorAxis;
  scalar eccentricity;
  scalar inclination;
  scalar argumentPeriapsis;
  scalar ascendingNode;
  scalar trueAnomaly;
};
} // namespace Ballistics23
