//
// Created by neodima on 20.02.24.
//

#include <gtest/gtest.h>

#include "utility/parser/BulletinParser.h"

#include "ephemeris/EphemerisCalculator.h"
#include "forces/AccelerationCalculator.h"
#include "forces/Gravity/CelestialGravity.h"
#include "forces/Gravity/EarthGravity.h"
#include "frame/FrameConverter.h"
#include "frame/PolarMotionContainer.h"
#include "time/DutCorrection.h"
#include "time/TimeConverter.h"

using namespace Ballistics23::Utility;
using namespace Ballistics23::Containers;

TEST(ACCELERATION, ALL) {
    const auto begin = static_cast<Ballistics23::scalar>(0);
    const auto end = static_cast<Ballistics23::scalar>(100000);

    const std::string currentDir = getRootPath(__FILE__, 4);
    const std::string csvPath = currentDir + "/data/frame/earth_rotation.csv";

    const Ballistics23::indexType mjdColInd = 3;
    const Ballistics23::indexType xpColInd = 4;
    const Ballistics23::indexType ypColInd = 5;
    const Ballistics23::indexType dutColInd = 6;

    vector<double> mjdData = getColumn(csvPath, mjdColInd, mjdColInd, begin, end);
    vector<double> xpData = getColumn(csvPath, xpColInd, mjdColInd, begin, end);
    vector<double> ypData = getColumn(csvPath, ypColInd, mjdColInd, begin, end);
    vector<double> dutData = getColumn(csvPath, dutColInd, mjdColInd, begin, end);

    const Ballistics23::FrameModule::PolarMotionContainer polarMotionContainer(mjdData, xpData, ypData);
    const Ballistics23::TimeModule::DutContainer dutContainer(mjdData, dutData);

    const Ballistics23::TimeModule::TimeConverter<Ballistics23::TimeModule::DutContainer> timeConverter(dutContainer);

    const Ballistics23::FrameModule::FrameConverter<Ballistics23::FrameModule::PolarMotionContainer,
                                                    Ballistics23::TimeModule::DutContainer>
        frameConverter(polarMotionContainer, timeConverter);

    const std::string ephemerisPath = currentDir + "/data/ephemeris/de405.bin";

    const Ballistics23::Ephemeris::EphemerisCalculator ephemerisCalculator(ephemerisPath);

    const std::string earthPath = currentDir + "/data/earthGravity";
    const Ballistics23::Force::EarthGravityForce earthGravity(earthPath, "egm96", 4, 4);

    const Ballistics23::Force::CelestialGravity celestialGravity;

    auto forcesTuple = std::tuple(celestialGravity);

    const Ballistics23::Force::AccelerationCalculator accelerationCalculator(
        timeConverter, frameConverter, ephemerisCalculator, earthGravity, forcesTuple);

    const Ballistics23::TimeModule::Time<Ballistics23::TimeModule::TimeScale::TT_SCALE> timeTT(2458119, 0.5);
    const Ballistics23::Vector3d position = {6800e3, 0, 0};
    const Ballistics23::Vector3d velocity = {0, std::sqrt(398600e9 / 6800e3), 0};
    const double mass = 1;

    decltype(accelerationCalculator)::allSatParams allSatParams;

    const Ballistics23::Vector3d acceleration = accelerationCalculator.calcAcceleration(
        earthGravity, forcesTuple, timeTT, position, velocity, mass, allSatParams);

    std::cout << acceleration;
}

TEST(ACCELERATION, GRAVITY) {
    const auto begin = static_cast<Ballistics23::scalar>(0);
    const auto end = static_cast<Ballistics23::scalar>(100000);

    const std::string currentDir = getRootPath(__FILE__, 4);
    const std::string csvPath = currentDir + "/data/frame/earth_rotation.csv";
    const Ballistics23::indexType mjdColInd = 3;
    const Ballistics23::indexType xpColInd = 4;
    const Ballistics23::indexType ypColInd = 5;
    const Ballistics23::indexType dutColInd = 6;

    vector<double> mjdData = getColumn(csvPath, mjdColInd, mjdColInd, begin, end);
    vector<double> xpData = getColumn(csvPath, xpColInd, mjdColInd, begin, end);
    vector<double> ypData = getColumn(csvPath, ypColInd, mjdColInd, begin, end);
    vector<double> dutData = getColumn(csvPath, dutColInd, mjdColInd, begin, end);

    const Ballistics23::FrameModule::PolarMotionContainer polarMotionContainer(mjdData, xpData, ypData);
    const Ballistics23::TimeModule::DutContainer dutContainer(mjdData, dutData);

    const Ballistics23::TimeModule::TimeConverter<Ballistics23::TimeModule::DutContainer> timeConverter(dutContainer);

    const Ballistics23::FrameModule::FrameConverter<Ballistics23::FrameModule::PolarMotionContainer,
                                                    Ballistics23::TimeModule::DutContainer>
        frameConverter(polarMotionContainer, timeConverter);

    const std::string ephemerisPath = currentDir + "/data/ephemeris/de405.bin";

    const Ballistics23::Ephemeris::EphemerisCalculator ephemerisCalculator(ephemerisPath);

    const std::string earthPath = currentDir + "/data/earthGravity";
    const Ballistics23::Force::EarthGravityForce earthGravity(earthPath, "egm96", 4, 4);
    const Ballistics23::Force::CelestialGravity celestialGravity;

    auto forcesTuple = std::tuple(celestialGravity);

    const Ballistics23::Force::AccelerationCalculator accelerationCalculator(
        timeConverter, frameConverter, ephemerisCalculator, earthGravity, forcesTuple);

    const Ballistics23::TimeModule::Time<Ballistics23::TimeModule::TimeScale::TT_SCALE> timeTT(2458119, 0.5);
    const Ballistics23::Vector3d position = {6800e3, 6800e3, 0};
    const Ballistics23::Vector3d velocity = {0, std::sqrt(398600e9 / 6800e3), 0};
    const double mass = 1;

    decltype(accelerationCalculator)::allSatParams allSatParams;

    const Ballistics23::Vector3d acceleration = accelerationCalculator.calcAcceleration(
        earthGravity, forcesTuple, timeTT, position, velocity, mass, allSatParams);

    std::cout << acceleration;
}