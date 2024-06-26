//
// Created by neodima on 20.02.24.
//

#pragma once

#include "Ballistics23/time/Time.h"
#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23::Force {

template <typename TimeConverter, typename FrameConverter, typename EphemerisCalculator, typename EarthGravity,
          typename... OtherForces>
class AccelerationCalculator {
    using TimeTT = TimeModule::Time<TimeModule::TimeScale::TT_SCALE>;

public:
    struct allSatParams : OtherForces::SatParams... {};

private:
    TimeConverter timeConverter_;
    FrameConverter frameConverter_;
    EphemerisCalculator ephemerisCalculator_;
    const EarthGravity &earthGravity_;
    std::tuple<OtherForces...> otherForces_;

    struct InputParams {
        Vector3d moonPositionGCRS;
        Vector3d jupiterPositionGCRS;
        Vector3d sunPositionGCRS;
        Vector3d sunVelocityGCRS;

        double moonGravParameter;
        double jupiterGravParameter;
        double sunGravParameter;
    };

    [[nodiscard]] InputParams calcInputParam(const TimeTT timeTT,
                                             const Quaternion<double> &quaternionGCRStoITRS) const noexcept {
        const TimeModule::Time<TimeModule::TimeScale::TDB_SCALE> timeTDB = timeConverter_.convertTT_TDB(timeTT);

        const auto stdToVector3d = [](const Containers::vector<double> &vector3) {
            return Vector3d{vector3[0], vector3[1], vector3[2]};
        };

        const int centerBody = 3;
        const Vector3d moonPositionGCRS = stdToVector3d(ephemerisCalculator_.calculateBodyR(10, centerBody, timeTDB));

        const Vector3d jupiterPositionGCRS = stdToVector3d(ephemerisCalculator_.calculateBodyR(5, centerBody, timeTDB));

        const Containers::vector<double> sunRVgcrs = ephemerisCalculator_.calculateBodyRV(11, centerBody, timeTDB);

        const Vector3d sunPositionGCRS = {sunRVgcrs[0], sunRVgcrs[1], sunRVgcrs[2]};
        const Vector3d sunVelocityGCRS = {sunRVgcrs[3], sunRVgcrs[4], sunRVgcrs[5]};

        const Vector3d moonPositionITRS = quaternionGCRStoITRS._transformVector(moonPositionGCRS);
        const Vector3d jupiterPositionITRS = quaternionGCRStoITRS._transformVector(jupiterPositionGCRS);
        const Vector3d sunPositionITRS = quaternionGCRStoITRS._transformVector(sunPositionGCRS);
        const Vector3d sunVelocityITRS = quaternionGCRStoITRS._transformVector(sunVelocityGCRS);

        const double muMoon = ephemerisCalculator_.calcGravParameter(10);
        const double muJupiter = ephemerisCalculator_.calcGravParameter(5);
        const double muSun = ephemerisCalculator_.calcGravParameter(11);

        return {moonPositionITRS, jupiterPositionITRS, sunPositionITRS, sunVelocityITRS, muMoon, muJupiter, muSun};
    }

    template <unsigned int... Is>
    [[nodiscard]] Vector3d auxFunction(const std::tuple<OtherForces...> &otherForces, const TimeTT timeTT,
                                       const Vector3d &positionGCRS, const Vector3d &velocityGCRS, scalar mass,
                                       const allSatParams &allSatParams, const InputParams &inputParams,
                                       std::integer_sequence<unsigned int, Is...>) const noexcept {
        return (std::get<Is>(otherForces)
                    .calcAcceleration(timeTT, positionGCRS, velocityGCRS, mass, allSatParams, inputParams) +
                ...);
    }

public:
    AccelerationCalculator(const TimeConverter &timeConverter, const FrameConverter &frameConverter,
                           const EphemerisCalculator &ephemerisCalculator, const EarthGravity &earthGravity,
                           const std::tuple<OtherForces...> &otherForces)
        : timeConverter_(timeConverter),
          frameConverter_(frameConverter),
          ephemerisCalculator_(ephemerisCalculator),
          earthGravity_(earthGravity),
          otherForces_(otherForces){};

    [[nodiscard]] Vector3d calcAcceleration(const TimeTT timeTT, const Vector3d &positionITRS,
                                            const Vector3d &velocityITRS, double mass,
                                            const allSatParams &allSatParams) const noexcept {
        const Quaternion<double> quaternionGCRStoITRS = frameConverter_.quaternionGCRStoITRS(timeTT);

        const InputParams inputParams = calcInputParam(timeTT, quaternionGCRStoITRS);

        const Vector3d earthGravAccelerationITRS = earthGravity_.calcAccelerationECEF(positionITRS);

        const Vector3d otherForcesAcceleration =
            auxFunction(otherForces_, timeTT, positionITRS, velocityITRS, mass, allSatParams, inputParams,
                        std::make_integer_sequence<unsigned int, sizeof...(OtherForces)>{});

        return earthGravAccelerationITRS + otherForcesAcceleration;
    }
};
}  // namespace Ballistics23::Force
