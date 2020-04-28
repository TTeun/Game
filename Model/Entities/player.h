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
        enum WallDirection { LEFT, RIGHT };

        void truncateHorizontalVelocity(const Physics::Constants & constants);

        void isNowWalled(WallDirection wallDirection);

        void isNowUnWalled();

        bool m_isWalled       = false;
        bool m_hasWallJumped  = false;
        float m_wallJumpDelay = 0.1f;
        sf::Clock m_timeSinceWalled;
        WallDirection m_wallDirection;
    };
} // namespace Entities

#endif // GAME_PLAYER_H
