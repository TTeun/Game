//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_ENEMY_H
#define TEUN_GAME_ENEMY_H

#include "../../View/drawable.h"
#include "../Physics/intersectableobject.h"
#include "ai.h"

namespace View {
    class DrawInterface;

    class Window;
} // namespace View

namespace Model {

    namespace Entities {

        class Enemy : public Physics::IntersectableObject, public Model::Entities::Ai, public View::Drawable {
        public:
            static Enemy create(const Geometry::Point & position);

            void draw(View::Window & window) const override;

        protected:
            void handleAi(float dt, const EntityController & entityController) override;

        private:
            Enemy(const sf::Vector2f & size, const Geometry::Point & position);
        };

    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_ENEMY_H
