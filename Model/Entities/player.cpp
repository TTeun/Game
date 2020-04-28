//
// Created by pc on 4/26/20.
//

#include "player.h"

#include "shapeFactory.h"

namespace Entities {

    Player::Player(float x, float y, float height, float width, const sf::Color & color)
        : Physics::IntersectableObject<Rectangle>(Rectangle(Point{width, height}, Point{x, y}, sf::Color::Green))
    {
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

    void Player::update(float dt, const Level & level, const Physics::Constants & constants)
    {
        truncateHorizontalVelocity(constants);
        if (m_isGrounded) {
            updateGrounded(dt, level, constants);
        } else {
            updateNotGrounded(dt, level, constants);
        }
        std::cout << m_isGrounded << ", " << m_isWalled << '\n';
    }

    void Player::updateNotGrounded(float dt, const Level & level, const Physics::Constants & constants)
    {
        PhysicsObject<Rectangle>::m_velocity.y += constants.m_gravitationalConstant * dt;
        IntersectionInfo info;
        const auto & terrainBlocks = level.getTerrainBlocks();
        for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
            info.update(intersect(*this, **it, dt));
        }
        if (info.type() == IntersectionInfo::Type::None) {
            Object<Rectangle>::m_shape.move(dt * PhysicsObject<Rectangle>::m_velocity);
        } else {
            handlePossibleIntersection(info, dt);
        }

        //        if (not m_isWalled) {
        //            PhysicsObject<Rectangle>::m_velocity.y += constants.m_gravitationalConstant * dt;
        //        } else {
        //            if (PhysicsObject<Rectangle>::m_velocity.y < 0.0f) {
        //                PhysicsObject<Rectangle>::m_velocity.y += constants.m_gravitationalConstant * dt;
        //            } else {
        //                PhysicsObject<Rectangle>::m_velocity.y = 0.99f * PhysicsObject<Rectangle>::m_velocity.y +
        //                0.01f * 40;
        //            }
        //        }
        //        IntersectionInfo info;
        //        const auto & terrainBlocks = level.getTerrainBlocks();
        //        for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
        //            info.update(intersect(*this, **it, dt));
        //        }
        //        if (info.type() == IntersectionInfo::Type::None) {
        //            Object<Rectangle>::m_shape.move(dt * PhysicsObject<Rectangle>::m_velocity);
        //        } else {
        //            handlePossibleIntersection(info, dt);
        //        }
    }

    void Player::handleHorizontalIntersection(const IntersectionInfo & info, float dt)
    {
        const auto horizontalIntersection = info.horizontalIntersection();
        switch (horizontalIntersection.second) {
            case IntersectionInfo::Type::None:
                isNowUnWalled();
                Object<Rectangle>::m_shape.move(sf::Vector2f(dt * PhysicsObject<Rectangle>::m_velocity.x, 0));
                break;
            case IntersectionInfo::Type::LeftToRight:
                isNowWalled(WallDirection::RIGHT);
                moveHorizontally(PhysicsObject<Rectangle>::m_velocity.x < 0, dt, horizontalIntersection.first);
                break;
            case IntersectionInfo::Type::RightToLeft:
                isNowWalled(WallDirection::LEFT);
                moveHorizontally(PhysicsObject<Rectangle>::m_velocity.x > 0, dt, horizontalIntersection.first);
                break;
            default: std::cout << "Rare horizontal intersection\n";
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
        if (std::abs(PhysicsObject<Rectangle>::m_velocity.x) > constants.m_maxHorizontalSpeed) {
            PhysicsObject<Rectangle>::m_velocity.x =
                (PhysicsObject<Rectangle>::m_velocity.x > 0.0f ? 1.0f : (-1.0f)) * constants.m_maxHorizontalSpeed;
        }
    }
} // namespace Entities