//
// Created by neodima on 09.11.23.
//

#pragma once

#include "Eigen/Core"
#include "Eigen/Dense"

namespace Ballistics23 {
using scalar = double;
using indexType = std::size_t;

using Vector3d = Eigen::Vector3<double>;
using Matrix3d = Eigen::Matrix<double, 3, 3>;

template<typename RealType> using Matrix3 = Eigen::Matrix<RealType,3,3>;


namespace Containers {

template <typename RealType> using vector = std::vector<RealType>;

template <typename RealType, indexType N> using array = std::array<RealType, N>;

using string = std::string;
} // namespace Containers

} // namespace Ballistics23
