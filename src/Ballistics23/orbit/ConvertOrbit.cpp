//
// Created by neodima on 10.06.24.
//

#include "ConvertOrbit.hpp"

namespace Ballistics23 {

Cartesian KeplerianToCartesian(const Keplerian& orbit, scalar gravityParameter) {
    const scalar semimajor = orbit.semiMajorAxis;
    const scalar ecc = orbit.eccentricity;
    const scalar inclination = orbit.inclination;
    const scalar argPeri = orbit.argumentPeriapsis;
    const scalar ascNode = orbit.ascendingNode;
    const scalar nu = orbit.trueAnomaly;

    const scalar p = semimajor * (1 - ecc * ecc);
    const scalar r = p / (1 + ecc * std::cos(nu));

    const scalar cosArgPeriAndNu = std::cos(argPeri + nu);
    const scalar sinArgPeriAndNu = std::sin(argPeri + nu);

    const scalar cosInc = std::cos(inclination);
    const scalar sinInc = std::sin(inclination);

    const scalar cosAscNode = std::cos(ascNode);
    const scalar sinAscNode = std::sin(ascNode);

    const scalar cosIncSinAscNode = cosInc * sinAscNode;
    const scalar cosIncCosAscNode = cosInc * cosAscNode;

    const Vector3d position =
        r * Vector3d((cosArgPeriAndNu * cosAscNode - cosIncSinAscNode * sinArgPeriAndNu),
                     (cosArgPeriAndNu * sinAscNode + cosIncCosAscNode * sinArgPeriAndNu), sinArgPeriAndNu * sinInc);

    const scalar cosNu = std::cos(nu);
    const scalar sinNu = std::sin(nu);

    const scalar sqrtGbyP = std::sqrt(gravityParameter / p);
    const scalar cosNuPlusEcc = cosNu + ecc;

    const scalar v1 = sqrtGbyP * sinNu;
    const scalar v2 = sqrtGbyP * cosNuPlusEcc;

    const scalar cosArgPeri = std::cos(argPeri);
    const scalar sinArgPeri = std::sin(argPeri);

    const Vector3d velocity(v2 * (-sinArgPeri * cosAscNode - cosIncSinAscNode * cosArgPeri) -
                                v1 * (cosArgPeri * cosAscNode - cosIncSinAscNode * sinArgPeri),
                            v2 * (-sinArgPeri * sinAscNode + cosIncCosAscNode * cosArgPeri) -
                                v1 * (cosArgPeri * sinAscNode + cosIncCosAscNode * sinArgPeri),
                            (v2 * cosArgPeri - v1 * sinArgPeri) * sinInc);
    return Cartesian{position, velocity};
};

[[nodiscard]] Keplerian CartesianToKeplerian(const Cartesian& orbit, scalar gravityParameter) {
    const Vector3d& position = orbit.position;
    const Vector3d& velocity = orbit.velocity;

    const scalar velocityNormSqr = velocity.squaredNorm();
    const scalar positionNorm = position.norm();

    const Vector3d orbitalMomentum = position.cross(velocity);  // орбитальный момент
    const Vector3d orbitalMomentumNormalized = orbitalMomentum.normalized();
    const Vector3d nodeVectorExp = Vector3d::UnitZ().cross(orbitalMomentum);  // вектор линии узлов
    const scalar nodeVectorExpNorm = nodeVectorExp.norm();
    const Vector3d e1 = nodeVectorExpNorm > 0 ? Vector3d(nodeVectorExp / nodeVectorExpNorm) : Vector3d::UnitX();

    const Vector3d eccentricityExp =
        ((velocityNormSqr - gravityParameter / positionNorm) * position - position.dot(velocity) * velocity) /
        gravityParameter;  // эксцентриситет(вектор)

    const scalar eccentricityExpNorm = eccentricityExp.norm();
    const Vector3d g1 = eccentricityExpNorm > 0 ? Vector3d(eccentricityExp / eccentricityExpNorm) : e1;

    const scalar semiMajorAxis = -gravityParameter / (velocityNormSqr - 2 * gravityParameter / positionNorm);  // большая полуось

    const scalar inclination = std::atan2(orbitalMomentum.dot(e1.cross(Vector3d::UnitZ())), orbitalMomentum.z());
    const scalar ascNode = std::atan2(e1.y(), e1.x());
    const scalar ex = g1.dot(e1), ey = g1.dot(orbitalMomentumNormalized.cross(e1));
    const scalar argPerig = std::atan2(ey, ex);
    const scalar posX = position.dot(g1), posY = position.dot(orbitalMomentumNormalized.cross(g1));
    const scalar anomaly = std::atan2(posY, posX);

    return Keplerian{semiMajorAxis,       eccentricityExpNorm, inclination,
                     normalize(argPerig), normalize(ascNode),  normalize(anomaly)};
};

}  // namespace Ballistics23