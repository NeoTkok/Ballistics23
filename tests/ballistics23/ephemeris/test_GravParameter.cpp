//
// Created by neodima on 17.12.23.
//

#include "Ballistics23/utility/parser/BulletinParser.h"
#include "ephemeris/EphemerisCalculator.h"
#include <gtest/gtest.h>

TEST(EPHEMERIS, GRAVPARAM) {

  const double tolerance = 1e-3;

  const std::string currentFile = __FILE__;
  const std::string currentDir =
      Ballistics23::Utility::getRootPath(currentFile, 4);
  const std::string ephemerisPath = currentDir + "/data/ephemeris/de405.bin";

  const Ballistics23::Ephemeris::EphemerisCalculator ephemerisCalculator(
      ephemerisPath);

  const double muMoon = ephemerisCalculator.calcGravParameter(10);
  const double muEarth = ephemerisCalculator.calcGravParameter(3);
  const double muJupiter = ephemerisCalculator.calcGravParameter(5);
  const double muSun = ephemerisCalculator.calcGravParameter(11);

  const double refMuMoon = 4.9028695e12;
  const double refMuEarth = 3.986004418e14;
  const double refJupiter = 1.26713e17;
  const double refMuSun = 1.32712440018e20;

  ASSERT_NEAR(std::abs(muMoon - refMuMoon) / refMuMoon, 0, tolerance);
  ASSERT_NEAR(std::abs(muEarth - refMuEarth) / refMuEarth, 0, tolerance);
  ASSERT_NEAR(std::abs(muJupiter - refJupiter) / muJupiter, 0, tolerance);
  ASSERT_NEAR(std::abs(muSun - refMuSun) / refMuSun, 0, tolerance);
}