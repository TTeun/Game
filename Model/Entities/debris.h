#ifndef SFML_DEBRIS_H
#define SFML_DEBRIS_H

#include "../Physics/deathtimer.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/ConvexShape.hpp>

class Uniform;

namespace Entities {

    class Debris : public Physics::IntersectableObject<sf::ConvexShape>, public Physics::DeathTimer {

    public:
        Debris(const sf::Vector2f & position,
               const sf::Color & color,
               const sf::Color & outlineColor,
               const Uniform & sizeUniform,
               const Uniform & directionUniform,
               const Uniform & numberOfPointsUniform);

        Debris(Debris && debris) = default;

        static sf::Vector2f getNormalizedRandomDirection(const Uniform & directionUniform);
    };
} // namespace Entities

#endif // SFML_DEBRIS_H
