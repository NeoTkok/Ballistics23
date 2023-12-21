//
// Created by neodima on 09.11.23.
//

#include "time.hpp"

namespace Ballistics23::Time {

    template<typename TimeScales>
    constexpr Time<TimeScales>::Time() noexcept : jdInt_(0), jdPart_(0) {}

    template<typename TimeScales>
    constexpr Time<TimeScales>::Time(double jdInt, double jdPart) noexcept : jdInt_(jdInt), jdPart_(jdPart) {};

    template<typename TimeScales>
    constexpr Time<TimeScales>::Time(double jd) noexcept : jdInt_(static_cast<int>(jd)), jdPart_(jd - jdInt_) {};

    template<typename TimeScales>
    constexpr Time<TimeScales> Time<TimeScales>::fromMJD(double mjd) noexcept {
        return Time<TimeScales>(mjd + delta_Jd_Mjd);
    }

    template<typename TimeScales>
    constexpr Time<TimeScales> Time<TimeScales>::fromCalendar(int year, int month, int day, int hour, int minutes,
                                                              int seconds) {
        double jdDay;
        double jdPart;
        //    iauDtf2d()...
        //    add except...
        return Time<TimeScales>(jdDay,jdPart);
    }

}