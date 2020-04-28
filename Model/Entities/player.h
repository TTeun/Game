//
// Created by pc on 4/26/20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Model {

    namespace Entities {

        class Level;

        class Player : public Physics::IntersectableObject {

        public:
            Player(float x, float y, float height, float width, const sf::Color & color);

            void addHorizontalForce(float force);

            void jump(const Physics::Constants & constants);

        private:
            void updateSnappedHorizontal(float dt, const Level & level, const Physics::Constants & constants) override;
        };
    } // namespace Entities
} // namespace Model
#endif // GAME_PLAYER_H
