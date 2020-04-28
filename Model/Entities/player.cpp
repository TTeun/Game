//
// Created by pc on 4/26/20.
//

#include "player.h"

#include "shapeFactory.h"

namespace Entities {

    Player::Player(float x, float y, float height, float width, const sf::Color & color)
        : Physics::IntersectableObject(Rectangle(Point{width, height}, Point{x, y}, sf::Color::Green))
    {
        setFeelsGravity(true);
    }

    void Player::addHorizontalForce(float force)
    {
        m_velocity.x += force / m_mass;
    }

    void Player::jump(const Physics::Constants & constants)
    {
        if (not m_hasWallJumped && (m_isWalled || m_timeSinceWalled.getElapsedTime().asSeconds() <= m_wallJumpDelay)) {
            m_isGrounded    = false;
            m_hasWallJumped = true;
            m_velocity.y    = -constants.m_wallJumpYVelocity;
            switch (m_wallDirection) {
                case WallDirection::RIGHT: m_velocity.x = -constants.m_wallJumpXVelocity; break;
                case WallDirection::LEFT: m_velocity.x = constants.m_wallJumpXVelocity; break;
            }
        } else if (m_isGrounded) {
            m_isGrounded = false;
            m_velocity.y = -constants.m_jumpVelocity;
        }
    }

    void Player::isNowWalled(const WallDirection wallDirection)
    {
        m_isWalled = true;
        m_timeSinceWalled.restart();
        m_wallDirection = wallDirection;
    }

    void Player::isNowUnWalled()
    {
        m_isWalled      = false;
        m_hasWallJumped = false;
    }

    void Player::truncateHorizontalVelocity(const Physics::Constants & constants)
    {
        if (std::abs(m_velocity.x) > constants.m_maxHorizontalSpeed) {
            m_velocity.x = (m_velocity.x > 0.0f ? 1.0f : (-1.0f)) * constants.m_maxHorizontalSpeed;
        }
    }
} // namespace Entities