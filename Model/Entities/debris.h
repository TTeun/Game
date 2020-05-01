#ifndef TEUN_GAME_DEBRIS_H
#define TEUN_GAME_DEBRIS_H

#include "../../View/drawable.h"
#include "../Physics/deathtimer.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/ConvexShape.hpp>

namespace Aux {
    class Uniform;
}

namespace Model {

    namespace Entities {

        class Debris : public Physics::IntersectableObject, public Physics::DeathTimer, public View::Drawable {

        public:
            void draw(View::Window & window) const override;

            static Debris create(const Geometry::Point & position);

            Debris(Debris && debris) = default;

        private:
            Debris(const Geometry::Point & position,
                   const Aux::Uniform & sizeUniform,
                   const Aux::Uniform & velocityUniform);

            static Geometry::Point getRandomVelocity(const Aux::Uniform & velocityUniform);
        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_DEBRIS_H
