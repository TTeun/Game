#include "intersectableobject.h"

#include "../Entities/level.h"

#include <iostream>

Model::Physics::IntersectableObject::IntersectableObject(Model::Shape::Rectangle && shape)
    : PhysicsObject(std::move(shape))
{
}

void Model::Physics::IntersectableObject::update(float dt,
                                                 const Model::Entities::Level & level,
                                                 const Constants & constants)
{
    if (m_snappedTerrainBlock) {
        updateSnapped(dt, level, constants);
    } else {
        updateUnSnapped(dt, level, constants);
    }
}

Model::Physics::IntersectableObject::WhereIsSnappedTerrain
Model::Physics::IntersectableObject::findWhereIsSnappedTerrain() const
{
    assert(m_snappedTerrainBlock);

    const auto thisTopLeft        = m_shape.topLeft();
    const auto thisBottomRight    = m_shape.bottomRight();
    const auto terrainTopLeft     = m_snappedTerrainBlock.get().getShape().topLeft();
    const auto terrainBottomRight = m_snappedTerrainBlock.get().getShape().bottomRight();

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

void Model::Physics::IntersectableObject::updateSnapped(float dt,
                                                        const Model::Entities::Level & level,
                                                        const Constants & constants)
{
    if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW ||
        m_whereIsSnappedTerrain == WhereIsSnappedTerrain::ABOVE) {
        updateSnappedVertical(dt, level, constants);
    } else {
        updateSnappedHorizontal(dt, level, constants);
    }
}

void Model::Physics::IntersectableObject::updateUnSnapped(float dt,
                                                          const Model::Entities::Level & level,
                                                          const Constants & constants)
{
    applyGravity(dt, constants);
    const auto movedRect = Model::Shape::Rectangle(m_shape).shrink(1.f) + dt * m_velocity;
    for (const auto & terrainBlock : level.getTerrainBlocks()) {
        if (terrainBlock->getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(terrainBlock.get());
            assert(m_snappedTerrainBlock);
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

void Model::Physics::IntersectableObject::updateSnappedVertical(float dt,
                                                                const Model::Entities::Level & level,
                                                                const Constants & constants)
{
    if (m_whereIsSnappedTerrain == WhereIsSnappedTerrain::BELOW) {
        const auto movedRect = m_shape + m_shape.height * 0.5f * Model::Shape::Point{0.0f, 1.0f};
        if (not m_snappedTerrainBlock.get().getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(nullptr);
        }
        m_shape.move(dt * m_velocity);
    } else {
        assert(m_whereIsSnappedTerrain == WhereIsSnappedTerrain::ABOVE);
        m_snappedTerrainBlock.set(nullptr);
    }
}

void Model::Physics::IntersectableObject::updateSnappedHorizontal(float dt,
                                                                  const Model::Entities::Level & level,
                                                                  const Constants & constants)
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
        }
        m_shape.move(dt * m_velocity);
    }
}
