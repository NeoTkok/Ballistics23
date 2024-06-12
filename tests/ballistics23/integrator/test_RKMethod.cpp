//
// Created by neodima on 11.06.24.
//

#include <gtest/gtest.h>

#include "ephemeris/EphemerisCalculator.h"
#include "forces/AccelerationCalculator.h"
#include "forces/Gravity/CelestialGravity.h"
#include "forces/Gravity/EarthGravity.h"
#include "frame/FrameConverter.h"
#include "frame/PolarMotionContainer.h"
#include "time/DutCorrection.h"
#include "time/TimeConverter.h"
#include "utility/parser/BulletinParser.h"
#include "integrator/RKMethod.hpp"
#include "right_hand_side/RV.hpp"


using namespace Ballistics23;
using namespace FrameModule;
using namespace TimeModule;

TEST(Integrator, test1) {
    const auto begin = static_cast<scalar>(0);
    const auto end = static_cast<scalar>(100000);

    const auto currentDir = Utility::getRootPath(__FILE__, 4);
    const auto csvPath = currentDir + "/data/frame/earth_rotation.csv";

    const indexType mjdColInd = 3, xpColInd = 4, ypColInd = 5, dutColInd = 6;
    const auto mjdData = Utility::getColumn(csvPath, mjdColInd, mjdColInd, begin, end);
    const auto xpData = Utility::getColumn(csvPath, xpColInd, mjdColInd, begin, end);
    const auto ypData = Utility::getColumn(csvPath, ypColInd, mjdColInd, begin, end);
    const auto dutData = Utility::getColumn(csvPath, dutColInd, mjdColInd, begin, end);

    const DutContainer dutContainer(mjdData, dutData);
    const TimeConverter<DutContainer> timeConverter(dutContainer);

    const PolarMotionContainer polarMotionContainer(mjdData, xpData, ypData);
    const FrameConverter<PolarMotionContainer, DutContainer> frameConverter(polarMotionContainer, timeConverter);

    const std::string ephemerisPath = currentDir + "/data/ephemeris/de405.bin";
    const Ephemeris::EphemerisCalculator ephemerisCalculator(ephemerisPath);

    const std::string earthPath = currentDir + "/data/earthGravity";
    const Force::EarthGravityForce earthGravity(earthPath, "egm96", 4, 4);

    const Force::CelestialGravity celestialGravity;

    auto forcesTuple = std::tuple(celestialGravity);

    const Force::AccelerationCalculator accelerationCalculator(timeConverter, frameConverter, ephemerisCalculator,
                                                               earthGravity, forcesTuple);

    const Time<TimeScale::TT_SCALE> timeTT(2458119, 0.5);
    const Vector3d position = {6800e3, 0, 0};
    const Vector3d velocity = {0, std::sqrt(398600e9 / 6800e3), 0};
    const double mass = 1;

    decltype(accelerationCalculator)::allSatParams allSatParams;

    const Vector3d acceleration = accelerationCalculator.calcAcceleration( timeTT, position,
                                                                          velocity, mass, allSatParams);

    const Ballistics23::RHS::RV RVcalculator(accelerationCalculator);
    const Ballistics23::scalar T = 2 * std::numbers::pi * 6800e3 * std::sqrt(6800e3 / 398600e9);
    const auto endTimeTT = timeTT + 2 * T;

    const Vector<scalar,6> initVector{position.x(),position.y(),position.z(), velocity.x(),velocity.y(),velocity.z()};
    const decltype(RVcalculator)::IntegrationState initialState{initVector, timeTT};

    const auto integrationResult = Ballistics23::integrate<decltype(RVcalculator), decltype(allSatParams)>(
        RVcalculator, initialState, endTimeTT, 10, allSatParams, mass);
    std::cout<< accelerationCalculator.calcAcceleration(timeTT,position,velocity,mass,allSatParams);
    const int z = 1;


}