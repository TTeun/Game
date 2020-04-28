#ifndef SFML_DEBRIS_H
#define SFML_DEBRIS_H

#include "../../Aux/uniform.h"
#include "../Physics/deathtimer.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/ConvexShape.hpp>

namespace Entities {

    class Debris : public Physics::IntersectableObject, public Physics::DeathTimer {

    public:
        Debris(const sf::Vector2f & position,
               const Uniform & sizeUniform,
               const Uniform & velocityUniform = Uniform{5, 2});

        Debris(Debris && debris) = default;

        static Point getRandomVelocity(const Uniform & directionUniform);
    };
} // namespace Entities

#endif // SFML_DEBRIS_H
