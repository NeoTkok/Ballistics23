//
// Created by neodima on 17.12.23.
//

#ifndef BALLISTICS2023_EPHEMERISCALCULATOR_H
#define BALLISTICS2023_EPHEMERISCALCULATOR_H

#include "Ballistics23/exceptions/Exceptions.h"
#include "Ballistics23/time/Time.h"
#include "CelestialBodies.h"
#include "calceph.h"

namespace Ballistics23::Ephemeris {

class EphemerisCalculator {
private:
  double AU;
  double EMRAT;

public:
  EphemerisCalculator(const Containers::string &path) {
    const int statusOpen = calceph_sopen(path.c_str());

    Ballistics23::Exceptions::ephemerisErrorHandler(statusOpen);

    const int statusConstant = calceph_sgetconstant("AU", &AU);

    Ballistics23::Exceptions::ephemerisErrorHandler(statusConstant);

    const int statusEMRAT = calceph_sgetconstant("EMRAT", &EMRAT);

    Ballistics23::Exceptions::ephemerisErrorHandler(statusEMRAT);
  }

  [[nodiscard]] Containers::vector<double> calculateBodyRV(
      const int targetBody, const int centerBody,
      const Ballistics23::TimeModule::Time<TimeModule::TimeScale::TDB_SCALE>
          &time) const {

    double PV[6];

    const auto jdInt = static_cast<double>(time.jdDayInt());
    const auto jdFrac = static_cast<double>(time.jdDayFrac());

    const int status =
        calceph_scompute(jdInt, jdFrac, targetBody, centerBody, PV);

    Ballistics23::Exceptions::ephemerisErrorHandler(status);

    const double AUe3 = AU * 1e3;
    const double AUe3divDay = AUe3 / 86400;
    const auto auToMeters = [&](const double distance) {
      return distance * AUe3;
    };
    const auto auPerDayToMetersPerSecond = [&](const double speed) {
      return speed * AUe3divDay;
    };
    return {auToMeters(PV[0]),
            auToMeters(PV[1]),
            auToMeters(PV[2]),
            auPerDayToMetersPerSecond(PV[3]),
            auPerDayToMetersPerSecond(PV[4]),
            auPerDayToMetersPerSecond(PV[5])};
  }

  [[nodiscard]] Containers::vector<double> calculateBodyR(
      const int targetBody, const int centerBody,
      const Ballistics23::TimeModule::Time<TimeModule::TimeScale::TDB_SCALE>
          &time) const {

    double PV[6];

    const auto jdInt = static_cast<double>(time.jdDayInt());
    const auto jdFrac = static_cast<double>(time.jdDayFrac());

    const int status =
        calceph_scompute(jdInt, jdFrac, targetBody, centerBody, PV);

    Ballistics23::Exceptions::ephemerisErrorHandler(status);

    const double AUe3 = AU * 1e3;
    const auto auToMeters = [&](const double distance) {
      return distance * AUe3;
    };

    return {auToMeters(PV[0]), auToMeters(PV[1]), auToMeters(PV[2])};
  }

  [[nodiscard]] double calcGravParameter(const int targetIndex) const {

    if (targetIndex >= 1 && targetIndex <= 11) {
      double gravParameter;
      char nameconstant[CALCEPH_MAX_CONSTANTNAME];

      const double multiplyFactor = (targetIndex == 3)    ? EMRAT / (EMRAT + 1)
                                    : (targetIndex == 10) ? 1 / (EMRAT + 1)
                                                          : 1;

      const int target = (targetIndex == 10)   ? 3
                         : (targetIndex == 11) ? 10
                                               : targetIndex;

      calceph_sgetconstantindex(8 + target, nameconstant, &gravParameter);

      const double AUe3 = AU * 1e3;
      const double AUe3divDaySec = AUe3 / 86400;
      const double AUe3divDaySecSqr = AUe3divDaySec * AUe3divDaySec;

      return gravParameter * AUe3 * AUe3divDaySecSqr * multiplyFactor;

    } else {
      throw Ballistics23::Exceptions::Exception("INAPPROPRIATE TARGET");
    }
  }
};
} // namespace Ballistics23::Ephemeris

#endif // BALLISTICS2023_EPHEMERISCALCULATOR_H