//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_PLAYER_H
#define TEUN_GAME_PLAYER_H

#include "../../View/drawable.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Model {

    namespace Entities {

        class Level;

        class Player : public Physics::IntersectableObject, public View::Drawable {

        public:
            Player(Geometry::ColoredRectangle && shape) : IntersectableObject(std::move(shape)){};

            Player(float x, float y, float height, float width, const sf::Color & color);

            void draw(View::Window & window) const override;

            void addHorizontalForce(float force);

            void jump(const Physics::Constants & constants);

        protected:
            void checkAndHandlePressedIntoWall(float dt, const Physics::Constants & constants) override;
        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_PLAYER_H
