//
// Created by neodima on 13.02.24.
//

#include "EarthGravity.h"

namespace Ballistics23::Force {

Vector3d EarthGravityForce::calcAccelerationECEF(const Ballistics23::Vector3d &positionECEF) const noexcept {
    double gx = 0;
    double gy = 0;
    double gz = 0;
    gravityModel.V(positionECEF.x(), positionECEF.y(), positionECEF.z(), gx, gy, gz);

    return {gx, gy, gz};
}
}  // namespace Ballistics23::Force
