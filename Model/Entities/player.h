//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_PLAYER_H
#define TEUN_GAME_PLAYER_H

#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Model {

    namespace Entities {

        class Level;

        class Player : public Physics::IntersectableObject {

        public:
            Player(float x, float y, float height, float width, const sf::Color &color);

            void addHorizontalForce(float force);

            void jump(const Physics::Constants &constants);

        private:
        protected:
            void checkAndHandlePressedIntoWall(float dt, const Physics::Constants &constants) override;

        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_PLAYER_H
