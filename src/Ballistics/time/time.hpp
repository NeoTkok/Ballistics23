//
// Created by neodima on 23.10.23.
//

#ifndef BALLISTICS23_TIME_HPP
#define BALLISTICS23_TIME_HPP

#include <array>
#include <string>
#include "sofa.h"


namespace Ballistics23::Time {

    enum class TimeScales {
        UT1_SCALE = 0,
        UTC_SCALE = 1,
        TAI_SCALE = 2,
        TT_SCALE = 3,
        TCG_SCALE = 4,
        TCB_SCALE = 5,
        TDB_SCALE = 6,
    };


    constexpr std::string_view UT1 = "ut1";
    constexpr std::string_view UTC = "UTC";
    constexpr std::string_view TAI = "TAI";
    constexpr std::string_view TT = "tt";
    constexpr std::string_view TCG = "tcg";
    constexpr std::string_view TCB = "tcb";
    constexpr std::string_view TDB = "tdb";
    constexpr std::array<std::string_view, 7> SCALES = {UT1, UTC, TAI, TT, TCG, TCB, TDB};


    template<typename TimeScales>
    class Time {
    private:
        double jdInt_;
        double jdPart_;
    public:
        static constexpr double delta_Jd_Mjd = 2400000 + 1. / 2;
//        static constexpr double SECS_PER_DAY = 86400;

        constexpr Time() noexcept;

        constexpr Time(double jdInt, double jdPart) noexcept;

        explicit constexpr Time(double jd) noexcept;

        [[nodiscard]] constexpr static Time fromMJD(double mjd) noexcept;


        [[nodiscard]] constexpr static Time fromCalendar(int year, int mounth, int day,
                                                         int hour, int minutes, int seconds);


    };

}  // namespace Ballistics23::Time



#endif //BALLISTICS23_TIME_HPP
