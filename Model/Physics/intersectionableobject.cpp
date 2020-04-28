//
// Created by pc on 4/28/20.
//

#include "intersectableobject.h"

#include <cassert>

namespace Physics {

    IntersectableObject::IntersectableObject(Rectangle && shape, const sf::Vector2f & velocity)
        : PhysicsObject(std::move(shape), velocity)
    {
    }

    IntersectableObject::IntersectableObject(Rectangle && shape) : PhysicsObject(std::move(shape))
    {
    }

    void IntersectableObject::update(float dt, const Entities::Level & level, const Constants & constants)
    {
        if (m_snappedTerrainBlock == nullptr) {
            updateUnSnapped(dt, level, constants);
        } else {
            updateSnapped(dt, level, constants);
        }
    }

    void IntersectableObject::setWhereIsSnappedTerrain()
    {
        const auto thisTopLeft        = m_shape.topLeft();
        const auto thisBottomRight    = m_shape.bottomRight();
        const auto terrainTopLeft     = m_snappedTerrainBlock->getShape().topLeft();
        const auto terrainBottomRight = m_snappedTerrainBlock->getShape().bottomRight();

        if (thisTopLeft.y < std::min(terrainTopLeft.y, terrainBottomRight.y) &&
            thisBottomRight.y <= std::min(terrainTopLeft.y, terrainBottomRight.y)) {
            m_whereIsSnappedTerrain = WhereIsSnappedTerrain::BELOW;
            return;
        } else if (thisTopLeft.x < std::max(terrainTopLeft.x, terrainBottomRight.x) &&
                   thisBottomRight.x <= std::max(terrainTopLeft.x, terrainBottomRight.x)) {
            m_whereIsSnappedTerrain = WhereIsSnappedTerrain::RIGHT;
            return;
        } else if (thisTopLeft.x >= std::min(terrainTopLeft.x, terrainBottomRight.x) &&
                   thisBottomRight.x > std::min(terrainTopLeft.x, terrainBottomRight.x)) {
            m_whereIsSnappedTerrain = WhereIsSnappedTerrain::LEFT;
            return;
        }
        assert(false);
    }
    void IntersectableObject::updateSnapped(float dt, const Entities::Level & level, const Constants & constants)
    {
        if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW) {
            updateSnappedBelow(dt, level, constants);
        } else {
            updateSnappedHorizontal(dt, level, constants);
        }
    }
    void IntersectableObject::updateUnSnapped(float dt, const Entities::Level & level, const Constants & constants)
    {
        applyGravity(dt, constants);
        const auto movedRect = Rectangle(m_shape).shrink(1.f) + dt * m_velocity;
        for (const auto & terrainBlock : level.getTerrainBlocks()) {
            if (terrainBlock->getShape().intersects(movedRect)) {
                m_snappedTerrainBlock = terrainBlock.get();
                assert(m_snappedTerrainBlock != nullptr);
                setWhereIsSnappedTerrain();
                if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW) {
                    m_velocity.y = 0.0f;
                } else {
                    m_velocity.x = 0.0f;
                }
                break;
            }
        }
        m_shape.move(dt * m_velocity);
    }
    void IntersectableObject::updateSnappedBelow(float dt, const Entities::Level & level, const Constants & constants)
    {
        const auto movedRect = m_shape + m_shape.height * 0.5f * Point{0.0f, 1.0f};
        if (not m_snappedTerrainBlock->getShape().intersects(movedRect)) {
            m_snappedTerrainBlock = nullptr;
        }
        m_shape.move(dt * m_velocity);
    }
    void
    IntersectableObject::updateSnappedHorizontal(float dt, const Entities::Level & level, const Constants & constants)
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
            }
            m_shape.move(dt * m_velocity);
        }
    }

} // namespace Physics