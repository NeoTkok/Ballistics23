//
// Created by neodima on 13.02.24.
//

#pragma once

#include "Ballistics23/utility/types/BasicTypes.h"
#include "Eigen/Dense"
#include "GeographicLib/GravityModel.hpp"

namespace Ballistics23::Force {
class EarthGravityForce {
private:
    GeographicLib::GravityModel gravityModel;

public:
    EarthGravityForce(const std::string &path, const std::string &gravityModelName, int maxN, int maxM)
        : gravityModel(gravityModelName, path, maxN, maxM){};

    [[nodiscard]] Vector3d calcAccelerationECEF(const Ballistics23::Vector3d &positionECEF) const noexcept;
};
}  // namespace Ballistics23::Force
