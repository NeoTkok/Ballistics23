//
// Created by neodima on 11.06.24.
//

#pragma once

#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23::ButcherTables {

class RK4ButcherTable {
public:
    constexpr static indexType nStages = 4;
    constexpr static std::array<scalar, nStages> c = {static_cast<scalar>(0), static_cast<scalar>(1) / 2,
                                                      static_cast<scalar>(1) / 2, static_cast<scalar>(1)};

    constexpr static std::array<scalar, nStages> b = {static_cast<scalar>(1) / 6, static_cast<scalar>(1) / 3,
                                                      static_cast<scalar>(1) / 3, static_cast<scalar>(1) / 6};

    constexpr static std::array<scalar, (nStages - 1) * nStages / 2> a = {
        static_cast<scalar>(1) / 2, static_cast<scalar>(0), static_cast<scalar>(1) / 2,
        static_cast<scalar>(0),     static_cast<scalar>(0), static_cast<scalar>(1)};
};

}  // namespace Ballistics23::ButcherTables