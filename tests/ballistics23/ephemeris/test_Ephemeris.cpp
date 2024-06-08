//
// Created by neodima on 17.12.23.
//

#include "ephemeris/EphemerisCalculator.h"
#include "ephemeris/ephemeris_result.h"
#include "time/DutCorrection.h"
#include "time/TimeConverter.h"
#include "utility/parser/BulletinParser.h"
#include <gtest/gtest.h>

TEST(EPHEMERIS, POSVEL) {
  const auto tolerance = static_cast<Ballistics23::scalar>(1);

  const std::string currentFile = __FILE__;
  const std::string ephemerisPath =
      currentFile.substr(0, currentFile.size() - 44) +
      "data/ephemeris/de405.bin";

  const Ballistics23::Ephemeris::EphemerisCalculator ephemerisCalculator(
      ephemerisPath);

  const auto begin = static_cast<Ballistics23::scalar>(0);
  const auto end = static_cast<Ballistics23::scalar>(100000);

  const Ballistics23::Containers::string mjdDutPath =
      "../../../data/frame/earth_rotation.csv";
  const Ballistics23::Utility::MJD_DUT mjd_dut =
      Ballistics23::Utility::CSVgetMJD_DUT(mjdDutPath, begin, end);

  const Ballistics23::TimeModule::DutContainer dutContainer(mjd_dut.mjdVector,
                                                            mjd_dut.dutVector);

  const Ballistics23::TimeModule::TimeConverter<
      Ballistics23::TimeModule::DutContainer>
      timeConverter(dutContainer);

  for (const auto &set : ephemeris_result) {

    const Ballistics23::TimeModule::Time<
        Ballistics23::TimeModule::TimeScale::TT_SCALE>
        tt(set[1], set[2]);
    const Ballistics23::TimeModule::Time<
        Ballistics23::TimeModule::TimeScale::TDB_SCALE>
        tdb = timeConverter
                  .convert<Ballistics23::TimeModule::TimeScale::TDB_SCALE>(tt);

    const auto targetBody = static_cast<int>(set[0]);
    const auto centerBody = 3;
    const Ballistics23::Containers::vector<double> result =
        ephemerisCalculator.calculateBodyRV(targetBody, centerBody, tdb);

    ASSERT_EQ(result.size(), 6);

    const Ballistics23::Containers::vector<double> reference = {
        set[3], set[4], set[5], set[6], set[7], set[8]};

    for (Ballistics23::indexType i = 0; i < reference.size(); ++i) {
      ASSERT_NEAR(result[i], reference[i], tolerance);
    }
  }
}

TEST(EPHEMERIS, POS) {
  const auto tolerance = static_cast<Ballistics23::scalar>(1);

  const std::string currentFile = __FILE__;
  const std::string ephemerisPath =
      currentFile.substr(0, currentFile.size() - 44) +
      "data/ephemeris/de405.bin";

  const Ballistics23::Ephemeris::EphemerisCalculator ephemerisCalculator(
      ephemerisPath);

  const auto begin = static_cast<Ballistics23::scalar>(0);
  const auto end = static_cast<Ballistics23::scalar>(100000);

  const Ballistics23::Containers::string mjdDutPath =
      "../../../data/frame/earth_rotation.csv";
  const Ballistics23::Utility::MJD_DUT mjd_dut =
      Ballistics23::Utility::CSVgetMJD_DUT(mjdDutPath, begin, end);

  getColumn(csvPath, dutColumnIndex, mjdColumnIndex, begin, end)

  const Ballistics23::TimeModule::DutContainer dutContainer(mjd_dut.mjdVector,
                                                            mjd_dut.dutVector);

  const Ballistics23::TimeModule::TimeConverter<
      Ballistics23::TimeModule::DutContainer>
      timeConverter(dutContainer);

  for (const auto &set : ephemeris_result) {

    const Ballistics23::TimeModule::Time<
        Ballistics23::TimeModule::TimeScale::TT_SCALE>
        tt(set[1], set[2]);
    const Ballistics23::TimeModule::Time<
        Ballistics23::TimeModule::TimeScale::TDB_SCALE>
        tdb = timeConverter
                  .convert<Ballistics23::TimeModule::TimeScale::TDB_SCALE>(tt);

    const auto targetBody = static_cast<int>(set[0]);
    const auto centerBody = 3;
    const Ballistics23::Containers::vector<double> result =
        ephemerisCalculator.calculateBodyR(targetBody, centerBody, tdb);

    ASSERT_EQ(result.size(), 3);

    const Ballistics23::Containers::vector<double> reference = {set[3], set[4],
                                                                set[5]};

    for (Ballistics23::indexType i = 0; i < reference.size(); ++i) {
      ASSERT_NEAR(result[i], reference[i], tolerance);
    }
  }
}
