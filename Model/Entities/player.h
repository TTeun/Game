//
// Created by pc on 4/26/20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "../../colors.h"
#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Entities {

    class Level;

    class Player : public Physics::IntersectableObject {

    public:
        Player(float x, float y, float height, float width, const sf::Color & color = Colors::playerColor);

        void addHorizontalForce(float force);

        void jump(const Physics::Constants & constants);

    private:
        void
        updateSnappedHorizontal(float dt, const Entities::Level & level, const Physics::Constants & constants) override;
    };
} // namespace Entities

#endif // GAME_PLAYER_H
