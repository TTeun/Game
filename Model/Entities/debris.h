#ifndef SFML_DEBRIS_H
#define SFML_DEBRIS_H

#include "../../Aux/uniform.h"
#include "../Physics/deathtimer.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/ConvexShape.hpp>

namespace Model {

    namespace Entities {

        class Debris : public Physics::PhysicsObject, public Physics::DeathTimer {

        public:
            static Debris create(const sf::Vector2f & position);

            Debris(Debris && debris) = default;

        private:
            Debris(const sf::Vector2f & position,
                   const Uniform & sizeUniform,
                   const Uniform & velocityUniform = Uniform{5, 2});

            static Shape::Point getRandomVelocity(const Uniform & velocityUniform);
        };
    } // namespace Entities
} // namespace Model
#endif // SFML_DEBRIS_H
