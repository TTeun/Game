#ifndef TEUN_GAME_DEBRIS_H
#define TEUN_GAME_DEBRIS_H

#include "../../Aux/uniform.h"
#include "../Physics/deathtimer.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/ConvexShape.hpp>

namespace Model {

    namespace Entities {

    class Debris : public Physics::IntersectableObject, public Physics::DeathTimer, public View::Drawable {

        public:
        void draw(View::Window &window) const override;

        static Debris create(const sf::Vector2f &position);

            Debris(Debris &&debris) = default;

        private:
            Debris(const sf::Vector2f &position,
                   const Aux::Uniform &sizeUniform,
                   const Aux::Uniform &velocityUniform = Aux::Uniform{5, 2});

            static Shapes::Point getRandomVelocity(const Aux::Uniform &velocityUniform);
        };
    } // namespace Entities
} // namespace Model
#endif // TEUN_GAME_DEBRIS_H
