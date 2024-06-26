//
// Created by neodima on 04.12.23.
//

#include <gtest/gtest.h>
#include "Ballistics23/time/Time.h"

using TimeScale = Ballistics23::TimeModule::TimeScale;
using TimeTT = Ballistics23::TimeModule::Time<TimeScale::TT_SCALE>;

TEST(TIME, JDINIT) {
    const TimeTT time(0, 0);

    ASSERT_DOUBLE_EQ(time.jdDayInt(), 0);
    ASSERT_DOUBLE_EQ(time.jdDayFrac(), 0);
}

TEST(TIME, GETTER) {
    const TimeTT timeTT(1000, 0.5);

    ASSERT_DOUBLE_EQ(timeTT.jdDayInt(), 1000);
    ASSERT_DOUBLE_EQ(timeTT.jdDayFrac(), 0.5);
    ASSERT_DOUBLE_EQ(timeTT.jd(), 1000.5);
    ASSERT_DOUBLE_EQ(timeTT.mjd(), 1000.5 - 2400000.5);
}

TEST(TIME, FABRICS) {
    const TimeTT timeTT1 = TimeTT::buildFromJD(2460220.);
    const TimeTT timeTT2 = TimeTT::buildFromMJD(2460220. - 2400000.5000);
    const TimeTT timeTT3 = Ballistics23::TimeModule::buildFromCalendar<TimeScale::TT_SCALE>(2023, 10, 2, 12, 0, 0.00);
    ASSERT_TRUE(timeTT1 == timeTT2);
    ASSERT_TRUE(timeTT2 == timeTT3);
}

TEST(TIME, OPERATIONS) {
    const TimeTT timeTT1 = TimeTT::buildFromJD(2460220.);

    ASSERT_DOUBLE_EQ(timeTT1 - timeTT1, 0);
    ASSERT_DOUBLE_EQ((timeTT1 - 2460220. * 86400 / 2).jd(), 1230110.);
    ASSERT_DOUBLE_EQ((timeTT1 + 2460220. * 86400 * 2).jd(), 2460220. * 3);
}
