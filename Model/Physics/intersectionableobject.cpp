#include "../Entities/level.h"
#include "intersectableobject.h"

#include <cassert>
#include <iostream>

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

    IntersectableObject::WhereIsSnappedTerrain IntersectableObject::findWhereIsSnappedTerrain() const
    {
        assert(m_snappedTerrainBlock);

        const auto thisTopLeft        = m_shape.topLeft();
        const auto thisBottomRight    = m_shape.bottomRight();
        const auto terrainTopLeft     = m_snappedTerrainBlock->getShape().topLeft();
        const auto terrainBottomRight = m_snappedTerrainBlock->getShape().bottomRight();

        if (thisBottomRight.y <= terrainTopLeft.y) {
            return WhereIsSnappedTerrain::BELOW;
        } else if (thisBottomRight.x <= terrainTopLeft.x) {
            return WhereIsSnappedTerrain::RIGHT;
        } else if (thisTopLeft.x >= terrainBottomRight.x) {
            return WhereIsSnappedTerrain::LEFT;
        } else if (thisTopLeft.y >= terrainBottomRight.y) {
            return WhereIsSnappedTerrain::ABOVE;
        }

        std::cout << thisBottomRight.y - terrainTopLeft.y << '\t' << thisBottomRight.x - terrainTopLeft.x << '\t'
                  << thisTopLeft.x - terrainBottomRight.x << '\t' << thisTopLeft.y - terrainBottomRight.y << '\n';

        assert(false);
    }

    void IntersectableObject::updateSnapped(float dt, const Entities::Level & level, const Constants & constants)
    {
        if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW ||
            m_whereIsSnappedTerrain == WhereIsSnappedTerrain::ABOVE) {
            updateSnappedVertical(dt, level, constants);
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
                m_whereIsSnappedTerrain = findWhereIsSnappedTerrain();
                if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW) {
                    m_velocity.y = 0.0f;
                } else if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::ABOVE) {
                    m_velocity.y = 0.0f;
                } else {
                    m_velocity.x = 0.0f;
                }
                break;
            }
        }
        m_shape.move(dt * m_velocity);
    }
    void
    IntersectableObject::updateSnappedVertical(float dt, const Entities::Level & level, const Constants & constants)
    {
        if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW) {
            const auto movedRect = m_shape + m_shape.height * 0.5f * Point{0.0f, 1.0f};
            if (not m_snappedTerrainBlock->getShape().intersects(movedRect)) {
                m_snappedTerrainBlock = nullptr;
            }
            m_shape.move(dt * m_velocity);
        } else {
            assert(m_whereIsSnappedTerrain == WhereIsSnappedTerrain::ABOVE);
            m_snappedTerrainBlock = nullptr;
        }
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