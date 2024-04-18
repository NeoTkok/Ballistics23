//
// Created by neodima on 09.12.23.
//

#include "frame/FrameConverter.h"
#include "frame/earth_rotation_result.hpp"
#include "time/DutCorrection.h"
#include "time/TimeConverter.h"
#include "utility/parser/BulletinParser.h"
#include "utility/types/BasicTypes.h"
#include <gtest/gtest.h>

TEST(CONVERTER, GCRS_ITRS) {
  using namespace Ballistics23::Utility;
  using namespace Ballistics23::Containers;
  using namespace Ballistics23::TimeModule;
  using namespace Ballistics23::FrameModule;
  const auto tolerance = static_cast<Ballistics23::scalar>(1);

  const auto begin = static_cast<Ballistics23::scalar>(0);
  const auto end = static_cast<Ballistics23::scalar>(100000);
  const std::string currentFile = __FILE__;
  const std::string currentDir = getRootPath(currentFile, 4);
  const std::string csvPath = currentDir + "/data/frame/earth_rotation.csv";
  const Ballistics23::indexType mjdColumnIndex = 3;
  const Ballistics23::indexType xpColumnIndex = 4;
  const Ballistics23::indexType ypColumnIndex = 5;
  const Ballistics23::indexType dutColumnIndex = 6;

  vector<double> mjdData = getColumn(csvPath, mjdColumnIndex, mjdColumnIndex, begin, end);

  vector<double> xpData = getColumn(csvPath, xpColumnIndex, mjdColumnIndex, begin, end);

  vector<double> ypData = getColumn(csvPath, ypColumnIndex, mjdColumnIndex, begin, end);

  vector<double> dutData = getColumn(csvPath, dutColumnIndex, mjdColumnIndex, begin, end);

  const PolarMotionContainer polarMotionContainer(mjdData, xpData, ypData);
  const DutContainer dutContainer(mjdData, dutData);

  const TimeConverter<DutContainer> timeConverter(dutContainer);
  const FrameConverter<PolarMotionContainer, DutContainer> frameConverter(
      polarMotionContainer, timeConverter);

  const Ballistics23::Vector3d gcrs1 = {6700e3, 0, 0};
  const Ballistics23::Vector3d gcrs2 = {0, 6700e3, 0};
  const Ballistics23::Vector3d gcrs3 = {0, 0, 6700e3};

  for (const auto &set : earthRotationResult) {

    const Time<TimeScale::TT_SCALE> tt =
        Time<TimeScale::TT_SCALE>::buildFromJD(set[0]);

    const Ballistics23::Matrix3d conversionMatrix =
        frameConverter.conversionMatrixGCRStoITRS(tt);

    const Ballistics23::Vector3d itrs1 = conversionMatrix * gcrs1;
    const Ballistics23::Vector3d itrs2 = conversionMatrix * gcrs2;
    const Ballistics23::Vector3d itrs3 = conversionMatrix * gcrs3;

    ASSERT_NEAR(itrs1(0), set[1], tolerance);
    ASSERT_NEAR(itrs1(1), set[2], tolerance);
    ASSERT_NEAR(itrs1(2), set[3], tolerance);

    ASSERT_NEAR(itrs2(0), set[4], tolerance);
    ASSERT_NEAR(itrs2(1), set[5], tolerance);
    ASSERT_NEAR(itrs2(2), set[6], tolerance);

    ASSERT_NEAR(itrs3(0), set[7], tolerance);
    ASSERT_NEAR(itrs3(1), set[8], tolerance);
    ASSERT_NEAR(itrs3(2), set[9], tolerance);
  }
}