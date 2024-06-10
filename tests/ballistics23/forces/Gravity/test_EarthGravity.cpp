//
// Created by neodima on 19.02.24.
//

#include "forces/Gravity/EarthGravity.h"
#include "Ballistics23/utility/parser/BulletinParser.h"
#include "fstream"
#include "utility/types/BasicTypes.h"
#include <gtest/gtest.h>

TEST(CALCFORCES, TEST) {
  using EGF = Ballistics23::Force::EarthGravityForce;
  using V3d = Ballistics23::Vector3d;

  const std::string currentFile = __FILE__;
  const std::string curDir = Ballistics23::Utility::getRootPath(currentFile, 4);
  const std::string modelPath = curDir + "/data/earthGravity";
  const std::string outputPath = curDir + "/data/output/garmonic";

  std::ofstream myfile(outputPath, std::ios::trunc);

  const EGF earthGravity1x1(modelPath, "egm96", 1, 1);
  const EGF earthGravity2x2(modelPath, "egm96", 2, 2);
  const EGF earthGravity3x3(modelPath, "egm96", 3, 3);
  const EGF earthGravity4x4(modelPath, "egm96", 4, 4);
  const EGF earthGravity16x16(modelPath, "egm96", 16, 16);
  const EGF earthGravity32x32(modelPath, "egm96", 32, 32);
  const EGF earthGravity64x64(modelPath, "egm96", 64, 64);
  const EGF earthGravity128x128(modelPath, "egm96", 128, 128);

  for (int i = 0; i < 177; i++) {
    double R = (200 * i + 6600) * 1e3;

    Ballistics23::scalar meanDiffByR1122 = 0;
    Ballistics23::scalar meanDiffByR2233 = 0;

    Ballistics23::scalar meanDiffByR128x64 = 0;
    Ballistics23::scalar meanDiffByR128x32 = 0;
    Ballistics23::scalar meanDiffByR128x16 = 0;
    Ballistics23::scalar meanDiffByR128x4 = 0;
    for (int m = 0; m < 100; m++) {
      for (int n = 0; n < 100; n++) {

        const double Tet = M_1_PI / 100 * m;
        const double Phi = 2 * M_1_PI / 100 * n;

        const V3d r = R * V3d(std::sin(Tet) * std::cos(Phi),
                              std::sin(Tet) * std::sin(Phi), std::cos(Tet));

        const V3d acceleration1x1 = earthGravity1x1.calcAccelerationECEF(r);
        const V3d acceleration2x2 = earthGravity2x2.calcAccelerationECEF(r);
        const V3d acceleration3x3 = earthGravity3x3.calcAccelerationECEF(r);
        const V3d acceleration4x4 = earthGravity4x4.calcAccelerationECEF(r);
        const V3d acceleration16x16 = earthGravity16x16.calcAccelerationECEF(r);
        const V3d acceleration32x32 = earthGravity32x32.calcAccelerationECEF(r);
        const V3d acceleration64x64 = earthGravity64x64.calcAccelerationECEF(r);
        const V3d acceleration128x128 =
            earthGravity128x128.calcAccelerationECEF(r);

        meanDiffByR1122 += (acceleration1x1 - acceleration2x2).norm();
        meanDiffByR2233 += (acceleration3x3 - acceleration2x2).norm();

        meanDiffByR128x64 += (acceleration128x128 - acceleration64x64).norm();
        meanDiffByR128x32 += (acceleration128x128 - acceleration32x32).norm();
        meanDiffByR128x16 += (acceleration128x128 - acceleration16x16).norm();
        meanDiffByR128x4 += (acceleration128x128 - acceleration4x4).norm();

        //                myfile << R << " " << x << " " << y << " " << z << " "
        //                << acceleration.x() << " " << acceleration.y() << " "
        //                       << acceleration.z() << std::endl;
      }
    }

    myfile << " " << R << " " << meanDiffByR1122 / 10000 << " "
           << meanDiffByR2233 / 10000 << " " << meanDiffByR128x64 / 10000 << " "
           << meanDiffByR128x32 / 10000 << " " << meanDiffByR128x16 / 10000
           << " " << meanDiffByR128x4 / 10000 << std::endl;
  }
}
