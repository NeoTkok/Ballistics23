//
// Created by neodima on 05.12.23.
//

#pragma once

#include "Ballistics23/utility/interpolator/LinearInterpolator.h"
#include "Time.h"

namespace Ballistics23::TimeModule {

class DutContainer {

private:
  Utility::Interpolator<scalar, scalar> interpolator;

public:
  DutContainer(const Containers::vector<scalar> &timePointsMJD,
               const Containers::vector<scalar> &dut) noexcept {

    Containers::vector<Utility::Interpolator<scalar, scalar>::XY> mjdDut(
        timePointsMJD.size());

    for (indexType i = 0; i < timePointsMJD.size(); ++i) {
      mjdDut[i] = {timePointsMJD[i], dut[i]};
    }

    interpolator = Utility::Interpolator<scalar, scalar>(mjdDut);
  };

  [[nodiscard]] scalar
  dut(const Time<TimeScale::UTC_SCALE> &timeUTC) const noexcept {
    return interpolator.interpolateDUT(timeUTC.mjd());
  }
};
} // namespace Ballistics23::TimeModule