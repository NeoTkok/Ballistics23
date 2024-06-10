//
// Created by neodima on 10.06.24.
//

#pragma once

#include "Cartesian.hpp"
#include "Keplerian.hpp"
#include "Ballistics23/utility/constants/MathConstants.h"

namespace Ballistics23 {

Cartesian KeplerianToCartesian(const Keplerian &orbit, scalar gravityParameter);

[[nodiscard]] Keplerian CartesianToKeplerian(const Cartesian &orbit, scalar gravityParameter);

scalar normalize(scalar number) {
    const scalar n = std::fmod(number, Ballistics23::PI2);
    return n >= 0 ? n : n + Ballistics23::PI2;
}

}  // namespace Ballistics23