//
// Created by neodima on 05.12.23.
//

#include <gtest/gtest.h>

#include "Ballistics23/time/DutCorrection.h"
#include "Ballistics23/time/TimeConverter.h"
#include "time/time_result.hpp"


TEST(CONVERT, UTC_UT1_TAI) {
  using namespace Ballistics23::TimeModule;
  const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
      -0.0320059, -0.0330198, -0.0340678, -0.0351611,
      -0.0361345, -0.0370076, -0.0377478};

  const Ballistics23::scalar timeStartMJD_UTC = 58480;

  Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(
      dutValues.size());

  for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
    timePointsMJD_UTC[i] =
        timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
  }

  const DutContainer dutContainer(timePointsMJD_UTC, dutValues);

  const TimeConverter<DutContainer> timeConverter(dutContainer);

  const Time<TimeScale::UTC_SCALE> utc(Ballistics23::timeResult[0][3],
                                       Ballistics23::timeResult[0][4]);

  const Time<TimeScale::UT1_SCALE> ut1 = timeConverter.convertUTC_UT1(utc);
  const Time<TimeScale::TAI_SCALE> tai = timeConverter.convertUTC_TAI(utc);

  const Time<TimeScale::UT1_SCALE> ut1_reference(
      Ballistics23::timeResult[0][1], Ballistics23::timeResult[0][2]);
  const Time<TimeScale::TAI_SCALE> tai_reference(
      Ballistics23::timeResult[0][5], Ballistics23::timeResult[0][6]);

  ASSERT_DOUBLE_EQ(ut1.jdDayInt(), ut1_reference.jdDayInt());
  ASSERT_DOUBLE_EQ(ut1.jdDayFrac(), ut1_reference.jdDayFrac());

  ASSERT_DOUBLE_EQ(tai.jdDayInt(), tai_reference.jdDayInt());
  ASSERT_DOUBLE_EQ(tai.jdDayFrac(), tai_reference.jdDayFrac());
}

TEST(CONVERT, MPI_UT1_UTC) {
  using namespace Ballistics23::TimeModule;

  const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
      -0.0320059, -0.0330198, -0.0340678, -0.0351611,
      -0.0361345, -0.0370076, -0.0377478};

  const Ballistics23::scalar timeStartMJD_UTC = 58480;

  Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(
      dutValues.size());

  for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
    timePointsMJD_UTC[i] =
        timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
  }

  const DutContainer dutContainer(timePointsMJD_UTC, dutValues);

  const TimeConverter<DutContainer> timeConverter(dutContainer);

  const Time<TimeScale::UTC_SCALE> utc_reference(
      Ballistics23::timeResult[0][3], Ballistics23::timeResult[0][4]);

  const Time<TimeScale::UT1_SCALE> ut1(Ballistics23::timeResult[0][1],
                                       Ballistics23::timeResult[0][2]);
  const Time<TimeScale::UTC_SCALE> utc = timeConverter.convertUT1_UTC(ut1);

  ASSERT_DOUBLE_EQ(utc.jdDayInt(), utc_reference.jdDayInt());
  ASSERT_DOUBLE_EQ(utc.jdDayFrac(), utc_reference.jdDayFrac());
}

TEST(CONVERT, TT_TDB) {
  using namespace Ballistics23::TimeModule;

  const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
      -0.0320059, -0.0330198, -0.0340678, -0.0351611,
      -0.0361345, -0.0370076, -0.0377478};

  const Ballistics23::scalar timeStartMJD_UTC = 58480;

  Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(
      dutValues.size());

  for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
    timePointsMJD_UTC[i] =
        timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
  }

  const DutContainer dutContainer(timePointsMJD_UTC, dutValues);

  const TimeConverter<DutContainer> timeConverter(dutContainer);

  const Time<TimeScale::TDB_SCALE> tdb_reference(
      Ballistics23::timeResult[0][13], Ballistics23::timeResult[0][14]);

  const Time<TimeScale::TT_SCALE> tt(Ballistics23::timeResult[0][7],
                                     Ballistics23::timeResult[0][8]);
  const Time<TimeScale::TDB_SCALE> tdb = timeConverter.convertTT_TDB(tt);

  ASSERT_DOUBLE_EQ(tdb.jdDayInt(), tdb_reference.jdDayInt());
  ASSERT_DOUBLE_EQ(tdb.jdDayFrac(), tdb_reference.jdDayFrac());
}

TEST(CONVERT, TDB_TT_MPI) {
  using namespace Ballistics23::TimeModule;

  const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
      -0.0320059, -0.0330198, -0.0340678, -0.0351611,
      -0.0361345, -0.0370076, -0.0377478};

  const Ballistics23::scalar timeStartMJD_UTC = 58480;

  Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(
      dutValues.size());

  for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
    timePointsMJD_UTC[i] =
        timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
  }

  const DutContainer dutContainer(timePointsMJD_UTC, dutValues);

  const TimeConverter<DutContainer> timeConverter(dutContainer);

  const Time<TimeScale::TDB_SCALE> tdb(Ballistics23::timeResult[0][13],
                                       Ballistics23::timeResult[0][14]);

  const Time<TimeScale::TT_SCALE> tt_reference(Ballistics23::timeResult[0][7],
                                               Ballistics23::timeResult[0][8]);
  const Time<TimeScale::TT_SCALE> tt = timeConverter.convertTDB_TT(tdb);

  ASSERT_DOUBLE_EQ(tt.jdDayInt(), tt_reference.jdDayInt());
  ASSERT_DOUBLE_EQ(tt.jdDayFrac(), tt_reference.jdDayFrac());
}
