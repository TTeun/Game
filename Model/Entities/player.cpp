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
        if (m_snappedTerrainBlock != nullptr) {
            switch (m_whereIsSnappedTerrain) {
                case Physics::IntersectableObject::WhereIsSnappedTerrain::BELOW:
                    m_velocity.y          = -constants.m_jumpVelocity;
                    m_snappedTerrainBlock = nullptr;
                    break;
                case Physics::IntersectableObject::WhereIsSnappedTerrain::RIGHT:
                    m_velocity.y          = -constants.m_jumpVelocity;
                    m_velocity.x          = -constants.m_wallJumpXVelocity;
                    m_snappedTerrainBlock = nullptr;
                    break;
                case Physics::IntersectableObject::WhereIsSnappedTerrain::LEFT:
                    m_velocity.y          = -constants.m_jumpVelocity;
                    m_velocity.x          = constants.m_wallJumpXVelocity;
                    m_snappedTerrainBlock = nullptr;
                    break;
                case Physics::IntersectableObject::WhereIsSnappedTerrain::ABOVE: break;
            }
        }

        //        if (not m_hasWallJumped && (m_isWalled || m_timeSinceWalled.getElapsedTime().asSeconds() <=
        //        m_wallJumpDelay)) {
        //            m_isGrounded    = false;
        //            m_hasWallJumped = true;
        //            m_velocity.y    = -constants.m_wallJumpYVelocity;
        //            switch (m_wallDirection) {
        //                case WallDirection::RIGHT: m_velocity.x = -constants.m_wallJumpXVelocity; break;
        //                case WallDirection::LEFT: m_velocity.x = constants.m_wallJumpXVelocity; break;
        //            }
        //        } else if (m_isGrounded) {
        //            m_isGrounded = false;
        //            m_velocity.y = -constants.m_jumpVelocity;
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
    void Player::updateSnappedHorizontal(float dt, const Level & level, const Physics::Constants & constants)
    {
        if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::RIGHT) {
            const auto movedRect = m_shape + m_shape.width * 0.5f * Point{1.0f, 0.0f};
            if (not m_snappedTerrainBlock->getShape().intersects(movedRect)) {
                m_snappedTerrainBlock = nullptr;
            }
            bool isPressingIntoWall = m_velocity.x > 0.0f;
            applyGravity(dt, constants);
            if (isPressingIntoWall) {
                m_velocity.x = 0.0f;
                if (m_velocity.y > 40) {
                    m_velocity.y = 40.0f;
                }
            }
            m_shape.move(dt * m_velocity);
        } else if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::LEFT) {
            const auto movedRect = m_shape + m_shape.width * 0.5f * Point{-1.0f, 0.0f};
            if (not m_snappedTerrainBlock->getShape().intersects(movedRect)) {
                m_snappedTerrainBlock = nullptr;
            }
            bool isPressingIntoWall = m_velocity.x < 0.0f;
            applyGravity(dt, constants);
            if (isPressingIntoWall) {
                m_velocity.x = 0.0f;
                if (m_velocity.y > 40) {
                    m_velocity.y = 40.0f;
                }
            }
            m_shape.move(dt * m_velocity);
        }
    }
} // namespace Entities