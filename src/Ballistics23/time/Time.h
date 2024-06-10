//
// Created by neodima on 29.11.23.
//

#pragma once

#include "sofa/sofa.h"

#include "Ballistics23/exceptions/Exceptions.h"
#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23::TimeModule {

enum class TimeScale {
    UT1_SCALE = 0,
    UTC_SCALE = 1,
    TAI_SCALE = 2,
    TT_SCALE = 3,
    TCG_SCALE = 4,
    TCB_SCALE = 5,
    TDB_SCALE = 6,
};

inline constexpr std::string_view UT1 = "ut1";
inline constexpr std::string_view UTC = "UTC";
inline constexpr std::string_view TAI = "TAI";
inline constexpr std::string_view TT = "tt";
inline constexpr std::string_view TCG = "tcg";
inline constexpr std::string_view TCB = "tcb";
inline constexpr std::string_view TDB = "tdb";
inline constexpr std::array<std::string_view, 7> SCALES = {UT1, UTC, TAI, TT, TCG, TCB, TDB};

template <TimeScale>
class Time {
    scalar jdDayInt_;
    scalar jdDayFrac_;

public:
    static constexpr scalar JD_MINUS_MJD = static_cast<scalar>(2400000) + static_cast<scalar>(0.5);
    static constexpr scalar SECS_PER_DAY = 86400;

    constexpr void align();

    constexpr Time() noexcept;

    constexpr Time(scalar jdInt, scalar jdFrac) noexcept;

    [[nodiscard]] constexpr static Time buildFromJD(scalar jd) noexcept;

    [[nodiscard]] constexpr static Time buildFromMJD(scalar mjd) noexcept;

    [[nodiscard]] constexpr scalar jdDayInt() const noexcept;

    [[nodiscard]] constexpr scalar jdDayFrac() const noexcept;

    [[nodiscard]] constexpr scalar jd() const noexcept;

    [[nodiscard]] constexpr scalar mjd() const noexcept;

    [[nodiscard]] constexpr TimeScale scale() const noexcept;

    [[nodiscard]] constexpr scalar operator-(const Time &other) const noexcept;

    [[nodiscard]] constexpr Time operator-(scalar seconds) const noexcept;

    [[nodiscard]] constexpr Time operator+(scalar seconds) const noexcept;

    [[nodiscard]] auto operator<=>(const Time &other) const noexcept = default;
};

template <TimeScale Scale>
constexpr Time<Scale> buildFromCalendar(int year, int month, int day, int hour, int minute, scalar seconds) {
    // потому что SOFA принимает double
    double jdDay;
    double jdDayPart;

    const int status =
        static_cast<int>(iauDtf2d(static_cast<std::string>(SCALES[static_cast<indexType>(Scale)]).c_str(), year, month,
                                  day, hour, minute, seconds, &jdDay, &jdDayPart));

    Exceptions::sofaErrorHandler(status);

    return Time<Scale>(static_cast<scalar>(jdDay), static_cast<scalar>(jdDayPart));
}

template <TimeScale Scale>
Time<Scale> constexpr Time<Scale>::buildFromJD(scalar jd) noexcept {
    return Time<Scale>(jd, static_cast<scalar>(0));
}

template <TimeScale Scale>
constexpr void Time<Scale>::align() {
    const int jdIntFloor =
        jdDayInt_ >= static_cast<scalar>(0) ? static_cast<int>(jdDayInt_) : static_cast<int>(jdDayInt_) - 1;
    const int jdFracFloor =
        jdDayFrac_ >= static_cast<scalar>(0) ? static_cast<int>(jdDayFrac_) : static_cast<int>(jdDayFrac_) - 1;

    const scalar jdIntDelta = jdDayInt_ - static_cast<scalar>(jdIntFloor);
    const scalar jdFracDelta = jdDayFrac_ - static_cast<scalar>(jdFracFloor);

    const scalar jdDeltasSum = jdIntDelta + jdFracDelta;

    if (jdDeltasSum >= static_cast<scalar>(1)) {
        jdDayInt_ = static_cast<scalar>(jdIntFloor + jdFracFloor + 1);
        jdDayFrac_ = jdDeltasSum - static_cast<scalar>(1);
    } else {
        jdDayInt_ = static_cast<scalar>(jdIntFloor + jdFracFloor);
        jdDayFrac_ = jdDeltasSum;
    }
}

template <TimeScale Scale>
constexpr Time<Scale>::Time() noexcept : jdDayInt_(static_cast<scalar>(0)), jdDayFrac_(static_cast<scalar>(0)) {}

template <TimeScale Scale>
constexpr Time<Scale>::Time(const scalar jdInt, const scalar jdFrac) noexcept : jdDayInt_(jdInt), jdDayFrac_(jdFrac) {
    align();
}

template <TimeScale Scale>
constexpr Time<Scale> Time<Scale>::buildFromMJD(scalar mjd) noexcept {
    return Time<Scale>(mjd, JD_MINUS_MJD);
}

template <TimeScale Scale>
constexpr scalar Time<Scale>::jdDayInt() const noexcept {
    return jdDayInt_;
}

template <TimeScale Scale>
constexpr scalar Time<Scale>::jdDayFrac() const noexcept {
    return jdDayFrac_;
}

template <TimeScale Scale>
constexpr scalar Time<Scale>::jd() const noexcept {
    return jdDayInt_ + jdDayFrac_;
}

template <TimeScale Scale>
constexpr scalar Time<Scale>::mjd() const noexcept {
    return (jdDayInt_ - JD_MINUS_MJD) + jdDayFrac_;
}

template <TimeScale Scale>
constexpr TimeScale Time<Scale>::scale() const noexcept {
    return Scale;
}

template <TimeScale Scale>
constexpr scalar Time<Scale>::operator-(const Time &other) const noexcept {
    const scalar jdIntDelta = jdDayInt_ - other.jdDayInt_;
    const scalar jdFracDelta = jdDayFrac_ - other.jdDayFrac_;
    return (jdIntDelta + jdFracDelta) * SECS_PER_DAY;
}

template <TimeScale Scale>
constexpr Time<Scale> Time<Scale>::operator-(const scalar seconds) const noexcept {
    return Time<Scale>(jdDayInt_, jdDayFrac_ - seconds / SECS_PER_DAY);
}

template <TimeScale Scale>
constexpr Time<Scale> Time<Scale>::operator+(const scalar seconds) const noexcept {
    return Time<Scale>(jdDayInt_, jdDayFrac_ + seconds / SECS_PER_DAY);
}

}  // namespace Ballistics23::TimeModule