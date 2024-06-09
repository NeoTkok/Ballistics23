//
// Created by neodima on 17.12.23.
//

#pragma once

namespace Ballistics23 {

// https://www.imcce.fr/content/medias/recherche/equipes/asd/calceph/calceph_c.pdf стр. 19
    enum class CelestialBodiesEnum {
        MERCURY = 1,
        VENUS = 2,
        EARTH = 3,
        MARS = 4,
        JUPITER = 5,
        SATURN = 6,
        URANUS = 7,
        NEPTUNE = 8,
        PLUTO = 9,
        MOON = 10,
        SUN = 11,
        SOLAR_SYSTEM_BARYCENTER = 12,
        EARTH_MOON_BARYCENTER = 13
    };
}
