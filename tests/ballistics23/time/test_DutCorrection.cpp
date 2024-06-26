//
// Created by neodima on 04.12.23.
//

#include <gtest/gtest.h>
#include <iostream>
#include "Ballistics23/time/DutCorrection.h"
#include "Ballistics23/time/Time.h"

using TimeUTC = Ballistics23::TimeModule::Time<Ballistics23::TimeModule::TimeScale::UTC_SCALE>;

TEST(INTERPOLATOR, MID_POINTS) {
    const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
        -0.11244, -0.11378, -0.11512, -0.11637, -0.11743, -0.11836, -0.11908, -0.11961, -0.12001, -0.12037, -0.12073};

    const Ballistics23::scalar timeStartMJD_UTC = 58480;
    const Ballistics23::scalar timeEndMJD_UTC = 58490;

    Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(dutValues.size());

    for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
        timePointsMJD_UTC[i] = timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
    }

    ASSERT_DOUBLE_EQ(timePointsMJD_UTC[0], timeStartMJD_UTC);
    ASSERT_DOUBLE_EQ(timePointsMJD_UTC[timePointsMJD_UTC.size() - 1], timeEndMJD_UTC);

    const Ballistics23::TimeModule::DutContainer dutContainer(timePointsMJD_UTC, dutValues);

    // mid-points test
    for (Ballistics23::indexType i = 0; i < dutValues.size() - 1; ++i) {
        const Ballistics23::scalar referenceInterpolatedDut = (dutValues[i] + dutValues[i + 1]) / 2;

        const Ballistics23::scalar midPointMJD_UTC = (timePointsMJD_UTC[i] + timePointsMJD_UTC[i + 1]) / 2;
        const TimeUTC utc = TimeUTC::buildFromMJD(midPointMJD_UTC);

        ASSERT_DOUBLE_EQ(utc.mjd(), midPointMJD_UTC);

        const Ballistics23::scalar dut = dutContainer.dut(utc);

        ASSERT_DOUBLE_EQ(dut, referenceInterpolatedDut);
    }
}

TEST(INTERPOLATOR, LEFT_POINTS) {
    const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
        -0.11244, -0.11378, -0.11512, -0.11637, -0.11743, -0.11836, -0.11908, -0.11961, -0.12001, -0.12037, -0.12073};

    const Ballistics23::scalar timeStartMJD_UTC = 58480;
    const Ballistics23::scalar timeEndMJD_UTC = 58490;

    Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(dutValues.size());

    for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
        timePointsMJD_UTC[i] = timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
    }

    ASSERT_DOUBLE_EQ(timePointsMJD_UTC[0], timeStartMJD_UTC);
    ASSERT_DOUBLE_EQ(timePointsMJD_UTC[timePointsMJD_UTC.size() - 1], timeEndMJD_UTC);

    const Ballistics23::TimeModule::DutContainer dutContainer(timePointsMJD_UTC, dutValues);

    // left-points test
    for (Ballistics23::indexType i = 0; i < dutValues.size() - 1; ++i) {
        const Ballistics23::scalar referenceInterpolatedDut = dutValues[i];

        const Ballistics23::scalar midPointMJD_UTC = timePointsMJD_UTC[i];
        const TimeUTC utc = TimeUTC::buildFromMJD(midPointMJD_UTC);

        ASSERT_DOUBLE_EQ(utc.mjd(), midPointMJD_UTC);

        const Ballistics23::scalar dut = dutContainer.dut(utc);

        ASSERT_DOUBLE_EQ(dut, referenceInterpolatedDut);
    }
}

TEST(INTERPOLATOR, RIGHT_POINTS) {
    const Ballistics23::Containers::vector<Ballistics23::scalar> dutValues = {
        -0.11244, -0.11378, -0.11512, -0.11637, -0.11743, -0.11836, -0.11908, -0.11961, -0.12001, -0.12037, -0.12073};

    const Ballistics23::scalar timeStartMJD_UTC = 58480;
    const Ballistics23::scalar timeEndMJD_UTC = 58490;

    Ballistics23::Containers::vector<Ballistics23::scalar> timePointsMJD_UTC(dutValues.size());

    for (Ballistics23::indexType i = 0; i < dutValues.size(); ++i) {
        timePointsMJD_UTC[i] = timeStartMJD_UTC + static_cast<Ballistics23::scalar>(i);
    }

    ASSERT_DOUBLE_EQ(timePointsMJD_UTC[0], timeStartMJD_UTC);
    ASSERT_DOUBLE_EQ(timePointsMJD_UTC[timePointsMJD_UTC.size() - 1], timeEndMJD_UTC);

    const Ballistics23::TimeModule::DutContainer dutContainer(timePointsMJD_UTC, dutValues);

    // right-points test
    for (Ballistics23::indexType i = 0; i < dutValues.size() - 1; ++i) {
        const Ballistics23::scalar referenceInterpolatedDut = dutValues[i + 1];

        const Ballistics23::scalar midPointMJD_UTC = timePointsMJD_UTC[i + 1];
        const TimeUTC utc = TimeUTC::buildFromMJD(midPointMJD_UTC);

        ASSERT_DOUBLE_EQ(utc.mjd(), midPointMJD_UTC);

        const Ballistics23::scalar dut = dutContainer.dut(utc);

        ASSERT_DOUBLE_EQ(dut, referenceInterpolatedDut);
    }
}
