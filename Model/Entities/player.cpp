//
// Created by pc on 4/26/20.
//

#include "player.h"

#include "terrainblock.h"

Model::Entities::Player::Player(float x, float y, float height, float width, const sf::Color & color)
    : Physics::IntersectableObject(
          Model::Shape::Rectangle(Model::Shape::Point{width, height}, Model::Shape::Point{x, y}, color))
{
    setFeelsGravity(true);
}

void Model::Entities::Player::addHorizontalForce(float force)
{
    m_velocity.x += force / m_mass;
}

void Model::Entities::Player::jump(const Physics::Constants & constants)
{
    if (m_snappedTerrainBlock) {
        switch (m_whereIsSnappedTerrain) {
            case Physics::IntersectableObject::WhereIsSnappedTerrain::BELOW:
                m_velocity.y = -constants.m_jumpVelocity;
                m_snappedTerrainBlock.set(nullptr);
                break;
            case Physics::IntersectableObject::WhereIsSnappedTerrain::RIGHT:
                m_velocity.y = -constants.m_jumpVelocity;
                m_velocity.x = -constants.m_wallJumpXVelocity;
                m_snappedTerrainBlock.set(nullptr);
                break;
            case Physics::IntersectableObject::WhereIsSnappedTerrain::LEFT:
                m_velocity.y = -constants.m_jumpVelocity;
                m_velocity.x = constants.m_wallJumpXVelocity;
                m_snappedTerrainBlock.set(nullptr);
                break;
            case Physics::IntersectableObject::WhereIsSnappedTerrain::ABOVE: break;
        }
    }
}

void Model::Entities::Player::updateSnappedHorizontal(float dt,
                                                      const Level & level,
                                                      const Physics::Constants & constants)
{
    if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::RIGHT) {
        const auto movedRect = m_shape + m_shape.width * 0.5f * Model::Shape::Point{1.0f, 0.0f};
        if (not m_snappedTerrainBlock.get().getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(nullptr);
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
        const auto movedRect = m_shape + m_shape.width * 0.5f * Model::Shape::Point{-1.0f, 0.0f};
        if (not m_snappedTerrainBlock.get().getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(nullptr);
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
