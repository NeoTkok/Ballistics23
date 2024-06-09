//
// Created by neodima on 13.02.24.
//

#ifndef BALLISTICS2023_CALCFORCES_H
#define BALLISTICS2023_CALCFORCES_H

#include "Ballistics23/utility/types/BasicTypes.h"
#include "Eigen/Dense"
#include "GeographicLib/GravityModel.hpp"

namespace Ballistics23::Force {
class EarthGravityForce {

private:
  GeographicLib::GravityModel gravityModel;

public:
  EarthGravityForce(const std::string &path,
                    const std::string &gravityModelName, int maxN, int maxM)
      : gravityModel(gravityModelName, path, maxN, maxM){};

  [[nodiscard]] Vector3d
  calcAccelerationECEF(const Ballistics23::Vector3d &rECEF) const noexcept;
};
} // namespace Ballistics23::Force

#endif // BALLISTICS2023_CALCFORCES_H
