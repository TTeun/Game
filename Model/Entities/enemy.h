//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_ENEMY_H
#define TEUN_GAME_ENEMY_H

#include "../Physics/intersectableobject.h"
#include "ai.h"
#include "../../View/drawable.h"

namespace View {
    class DrawInterface;

    class Window;
}


namespace Model {

    namespace Entities {

        class Enemy : public Physics::IntersectableObject, public Model::Entities::Ai, public View::Drawable {
        public:
            static Enemy create(const sf::Vector2f &position);

            void draw(View::Window &window) const override;

        protected:
            void handleAi(float dt, const EntityController &entityController) override;

        private:
            Enemy(const sf::Vector2f &size, const sf::Vector2f &position);
        };


    } // namespace Entities

} // namespace Model
#endif // TEUN_GAME_ENEMY_H
