//
// Created by neodima on 08.12.23.
//

#pragma once

#include "Ballistics23/time/TimeConverter.h"

namespace Ballistics23::FrameModule {

struct PolarMotion {
    scalar xp_;
    scalar yp_;
};

class PolarMotionContainer {
    // Времена
    Containers::vector<scalar> timeData_;  // UTC MJD
    // Параметры полярного движения
    Containers::vector<PolarMotion> polarMotionData_;

public:
    PolarMotionContainer(const Containers::vector<scalar> &timeData, const Containers::vector<scalar> &xp,
                         const Containers::vector<scalar> &yp) noexcept
        : timeData_(timeData) {
        const indexType size = timeData_.size();
        polarMotionData_.resize(size);

        for (indexType i = 0; i < size; ++i) {
            polarMotionData_[i] = {xp[i], yp[i]};
        }
    }

    [[nodiscard]] PolarMotion getPolarMotion(const TimeModule::Time<TimeModule::TimeScale::UTC_SCALE> &utc) const;
};

PolarMotion PolarMotionContainer::getPolarMotion(const TimeModule::Time<TimeModule::TimeScale::UTC_SCALE> &utc) const {
    const scalar utcMjd = utc.mjd();
    for (indexType i = 0; i < timeData_.size() - 1; ++i) {
        if ((utcMjd >= timeData_[i]) && (utcMjd < timeData_[i + 1])) {
            const scalar dY = polarMotionData_[i + 1].yp_ - polarMotionData_[i].yp_;
            const scalar dX = polarMotionData_[i + 1].xp_ - polarMotionData_[i].xp_;

            const scalar denominator = timeData_[i + 1] - timeData_[i];
            const scalar coeff = (utcMjd - timeData_[i]) / denominator;

            const scalar yp = polarMotionData_[i].yp_ + dY * coeff;
            const scalar xp = polarMotionData_[i].xp_ + dX * coeff;

            return {xp, yp};
        }
    }

    if (utcMjd == timeData_[timeData_.size() - 1]) {
        return {polarMotionData_[polarMotionData_.size() - 1].xp_, polarMotionData_[polarMotionData_.size() - 1].yp_};
    }

    throw Exceptions::Exception("POLAR MOTION INTERPOLATOR ERROR: VALUE OUT OF BOUNDS");
}
}  // namespace Ballistics23::FrameModule