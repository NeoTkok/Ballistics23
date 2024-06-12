//
// Created by neodima on 11.06.24.
//

#pragma once

#include "Ballistics23/forces/AccelerationCalculator.h"
#include "Ballistics23/time/Time.h"
#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23::RHS {

template <typename CalcAcceleration>
class RV {
    CalcAcceleration accelerationCalculator_;

public:
    explicit RV(const CalcAcceleration &accelerationCalculator) : accelerationCalculator_(accelerationCalculator){};

    using ArgumentType = TimeModule::Time<TimeModule::TimeScale::TT_SCALE>;
    using IntegrationVector = Vector<scalar, 6>;

    struct IntegrationState {
        IntegrationVector vector;
        ArgumentType argument;
    };

    [[nodiscard]] inline IntegrationVector calc(const IntegrationState &state,
                                                const CalcAcceleration::allSatParams &satParams,
                                                const Ballistics23::scalar mass) const noexcept {
        const auto pos = state.vector.template segment<3>(0);
        const auto vel = state.vector.template segment<3>(3);
        const auto accel = accelerationCalculator_.calcAcceleration(state.argument, pos, vel, mass, satParams);

        IntegrationVector result;
        result.segment<3>(0) = state.vector.template segment<3>(3);
        result.segment<3>(3) = accel;

        return result;
    }
};

}  // namespace Ballistics23::RHS