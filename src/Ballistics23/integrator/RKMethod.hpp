//
// Created by neodima on 11.06.24.
//

#pragma once

#include "Ballistics23/forces/AccelerationCalculator.h"
#include "Ballistics23/right_hand_side/RV.hpp"
#include "Ballistics23/time/Time.h"
#include "Ballistics23/utility/types/BasicTypes.h"
#include "Butcher_table.hpp"

namespace Ballistics23 {

template <typename RHS, typename SatParam>
[[nodiscard]] typename RHS::IntegrationState integrateOneStep(
    const RHS &rhs, const typename RHS::IntegrationState &initialIntegrationState, const scalar &step,
    SatParam &satParam, const scalar mass) {
    const auto currentIntegrationState = initialIntegrationState;

    Containers::array<Vector<scalar, 6>, ButcherTables::RK4ButcherTable::nStages> k;

    for (indexType i = 0; i < ButcherTables::RK4ButcherTable::nStages; ++i) {
        Vector<scalar, 6> vec = Vector<scalar, 6>::Zero();
        for (indexType j = 0; j < i; ++j) {
            vec += ButcherTables::RK4ButcherTable::a[i * (i - 1) / 2 + j] * k[j];
        }

        vec *= step;

        vec += currentIntegrationState.vector;
        const auto newState{currentIntegrationState.argument + ButcherTables::RK4ButcherTable::c[i] * step};
        k[i] = rhs.calc({vec, newState}, satParam, mass);
    }

    typename RHS::IntegrationVector result = RHS::IntegrationVector::Zero();

    for (indexType i = 0; i < ButcherTables::RK4ButcherTable::nStages; ++i) {
        result += ButcherTables::RK4ButcherTable::b[i] * k[i];
    }

    result *= step;

    result += currentIntegrationState.vector;

    const typename RHS::IntegrationState integrationState = {result, initialIntegrationState.argument + step};

    return integrationState;
}

template <typename RHS, typename SatParam>
[[nodiscard]] Containers::vector<typename RHS::IntegrationState> integrate(
    const RHS &rhs, const typename RHS::IntegrationState &initialState,
    const decltype(RHS::IntegrationState::argument) &endPointArgument, const scalar step, SatParam &satParam,
    const scalar mass) {
    const auto size = static_cast<indexType>((endPointArgument - initialState.argument) / step) + 2;

    Containers::vector<typename RHS::IntegrationState> output(size);
    output[0] = initialState;

    for (indexType i = 1; i < size - 1; ++i) {
        output[i] = Ballistics23::integrateOneStep(rhs, output[i - 1], step, satParam, mass);
    }

    const auto lastIntervalStep = endPointArgument - output[size - 2].argument;
    output.push_back(Ballistics23::integrateOneStep(rhs, output[size - 2], lastIntervalStep, satParam, mass));

    return output;
}

}  // namespace Ballistics23