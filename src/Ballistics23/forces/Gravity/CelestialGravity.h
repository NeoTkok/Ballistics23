//
// Created by neodima on 13.02.24.
//

#pragma once

#include "Ballistics23/time/Time.h"
#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23::Force {

class CelestialGravity {

  [[nodiscard]] Vector3d
  calcAccelerationSingleBody(const Vector3d &relativePosition,
                             const double gravParameter) const noexcept {

    const double distanceSqr = relativePosition.squaredNorm();
    const double distance = std::sqrt(distanceSqr);
    const double distanceCube = distanceSqr * distance;

    return (-gravParameter / distanceCube) * relativePosition;
  }

public:
  struct SatParams {};

  template <typename InputParams>
  [[nodiscard]] Vector3d calcAcceleration(
      const TimeModule::Time<TimeModule::TimeScale::TT_SCALE> &timeTT,
      const Vector3d &positionGCRS, const Vector3d &velocityGCRS,
      const double mass, const SatParams satParams,
      const InputParams inputParams) const noexcept {

    const Vector3d moonAcceleration =
        calcAccelerationSingleBody(positionGCRS - inputParams.moonPositionGCRS,
                                   inputParams.moonGravParameter);
    const Vector3d jupiterAcceleration = calcAccelerationSingleBody(
        positionGCRS - inputParams.jupiterPositionGCRS,
        inputParams.jupiterGravParameter);
    const Vector3d sunAcceleration =
        calcAccelerationSingleBody(positionGCRS - inputParams.sunPositionGCRS,
                                   inputParams.sunGravParameter);

    const Vector3d resultAcceleration =
        moonAcceleration + jupiterAcceleration + sunAcceleration;

    return resultAcceleration;
  }
};

} // namespace Ballistics23::Force
