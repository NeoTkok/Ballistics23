//
// Created by neodima on 10.06.24.
//

#include <gtest/gtest.h>
#include "Ballistics23/orbit/ConvertOrbit.hpp"
using namespace Ballistics23;

struct NumericLimits {
    static constexpr scalar relativeTolerance = std::numeric_limits<scalar>::epsilon();
};

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_1) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = 0;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = 0;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(semimajor, 0, 0);
    const Vector3d referenceVelocity(0, std::sqrt(gravParam / referencePosition.norm()), 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_2) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = 0;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(0, semimajor, 0);
    const Vector3d referenceVelocity(-std::sqrt(gravParam / referencePosition.norm()), 0, 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_3) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = 0;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = PI;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(-semimajor, 0, 0);
    const Vector3d referenceVelocity(0, -std::sqrt(gravParam / referencePosition.norm()), 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_4) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = 0;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = 3 * PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(0, -semimajor, 0);
    const Vector3d referenceVelocity(std::sqrt(gravParam / referencePosition.norm()), 0, 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_5) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = 0;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(semimajor, 0, 0);
    const Vector3d referenceVelocity(0, -std::sqrt(gravParam / referencePosition.norm()), 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_6) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(0, -semimajor, 0);
    const Vector3d referenceVelocity(-std::sqrt(gravParam / referencePosition.norm()), 0, 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_7) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = PI;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(-semimajor, 0, 0);
    const Vector3d referenceVelocity(0, std::sqrt(gravParam / referencePosition.norm()), 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_8) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = 3 * PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(0, semimajor, 0);
    const Vector3d referenceVelocity(std::sqrt(gravParam / referencePosition.norm()), 0, 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_9) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI / 2;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = 0;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(semimajor, 0, 0);
    const Vector3d referenceVelocity(0, 0, std::sqrt(gravParam / referencePosition.norm()));
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_10) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI / 2;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(0, 0, semimajor);
    const Vector3d referenceVelocity(-std::sqrt(gravParam / referencePosition.norm()), 0, 0);
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_11) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI / 2;
    const scalar argPerig = 0;
    const scalar ascNode = 0;
    const scalar anomaly = PI;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(-semimajor, 0, 0);
    const Vector3d referenceVelocity(0, 0, -std::sqrt(gravParam / referencePosition.norm()));
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_12) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI / 2;
    const scalar argPerig = 0;
    const scalar ascNode = PI;
    const scalar anomaly = 0;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(-semimajor, 0, 0);
    const Vector3d referenceVelocity(0, 0, std::sqrt(gravParam / referencePosition.norm()));
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_13) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI / 2;
    const scalar argPerig = PI / 2;
    const scalar ascNode = PI;
    const scalar anomaly = PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(semimajor, 0, 0);
    const Vector3d referenceVelocity(0, 0, -std::sqrt(gravParam / referencePosition.norm()));
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}

TEST(KEPLERIAN_AND_CARTESIAN, SINGULAR_14) {
    const scalar gravParam = 3.9860044158e14;
    const scalar semimajor = 6800e3;
    const scalar ecc = 0.;
    const scalar incl = PI / 2;
    const scalar argPerig = PI / 2;
    const scalar ascNode = PI;
    const scalar anomaly = PI / 2;

    const Keplerian keplerianTrueInitial{semimajor, ecc, incl, argPerig, ascNode, anomaly};
    const auto cart = KeplerianToCartesian(keplerianTrueInitial, gravParam);
    const Vector3d referencePosition(semimajor, 0, 0);
    const Vector3d referenceVelocity(0, 0, -std::sqrt(gravParam / referencePosition.norm()));
    ASSERT_NEAR((cart.position - referencePosition).norm() / referencePosition.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    ASSERT_NEAR((cart.velocity - referenceVelocity).norm() / referenceVelocity.norm(), 0,
                10 * NumericLimits::relativeTolerance);
    const auto resultKeplerian = CartesianToKeplerian(cart, gravParam);
    const auto resultCartesian = KeplerianToCartesian(resultKeplerian, gravParam);
    ASSERT_NEAR((resultCartesian.position - cart.position).norm() / resultCartesian.position.norm(), 0.,
                100 * NumericLimits::relativeTolerance);
}
