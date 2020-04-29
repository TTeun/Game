#include "intersectableobject.h"

#include "../Entities/level.h"

#include <iostream>

Model::Physics::IntersectableObject::IntersectableObject(Model::Shape::Rectangle &&shape)
        : PhysicsObject(std::move(shape)) {
}

void Model::Physics::IntersectableObject::update(float dt,
                                                 const Model::Entities::Level &level,
                                                 const Constants &constants) {
    if (m_snappedTerrainBlock) {
        updateSnapped(dt, level, constants);
    } else {
        updateUnSnapped(dt, level, constants);
    }
}

Model::Physics::IntersectableObject::WHERE_IS_SNAPPED_TERRAIN
Model::Physics::IntersectableObject::whichDirectionIsTerrainBlock(
        const Model::Entities::TerrainBlock &snappedTerrainBlock) const {

    const auto thisTopLeft = m_shape.topLeft();
    const auto thisBottomRight = m_shape.bottomRight();
    const auto terrainTopLeft = snappedTerrainBlock.getShape().topLeft();
    const auto terrainBottomRight = snappedTerrainBlock.getShape().bottomRight();

    if (thisBottomRight.y <= terrainTopLeft.y) {
        return WHERE_IS_SNAPPED_TERRAIN::BELOW;
    } else if (thisBottomRight.x <= terrainTopLeft.x) {
        return WHERE_IS_SNAPPED_TERRAIN::RIGHT;
    } else if (thisTopLeft.x >= terrainBottomRight.x) {
        return WHERE_IS_SNAPPED_TERRAIN::LEFT;
    } else if (thisTopLeft.y >= terrainBottomRight.y) {
        return WHERE_IS_SNAPPED_TERRAIN::ABOVE;
    }

    std::cout << thisBottomRight.y - terrainTopLeft.y << '\t' << thisBottomRight.x - terrainTopLeft.x << '\t'
              << thisTopLeft.x - terrainBottomRight.x << '\t' << thisTopLeft.y - terrainBottomRight.y << '\n';

//    assert(false);
}

void Model::Physics::IntersectableObject::updateSnapped(float dt,
                                                        const Model::Entities::Level &level,
                                                        const Constants &constants) {
    if (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::BELOW ||
        m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::ABOVE) {
        updateSnappedHorizontal(dt, level, constants);
    } else {
        updateSnappedVertical(dt, level, constants);
    }
}

void Model::Physics::IntersectableObject::updateUnSnapped(float dt,
                                                          const Model::Entities::Level &level,
                                                          const Constants &constants) {
    applyGravity(dt, constants);
    const auto movedRect = Model::Shape::Rectangle(m_shape).shrink(1.f) + dt * m_velocity;
    for (const auto &terrainBlock : level.getTerrainBlocks()) {
        if (terrainBlock->getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(terrainBlock.get());
            assert(m_snappedTerrainBlock);
            m_whereIsSnappedTerrain = whichDirectionIsTerrainBlock(m_snappedTerrainBlock.get());
            if (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::BELOW) {
                m_velocity.y = 0.0f;
            } else if (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::ABOVE) {
                m_velocity.y = 0.0f;
            } else {
                m_velocity.x = 0.0f;
            }
            break;
        }
    }
    m_shape.move(dt * m_velocity);
}

void Model::Physics::IntersectableObject::updateSnappedHorizontal(float dt,
                                                                  const Model::Entities::Level &level,
                                                                  const Constants &constants) {
    if (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::BELOW) {
        const auto lowerRect = m_shape + m_shape.height * 0.5f * Model::Shape::Point{0.0f, 1.0f};
        if (not m_snappedTerrainBlock.get().getShape().intersects(lowerRect)) {
            unSnap();
        }
        m_velocity.y = 0.0f;

        const auto movedRect = Model::Shape::Rectangle(m_shape).shrink(1.f) + dt * m_velocity;
        for (const auto &terrainBlock : level.getTerrainBlocks()) {
            if (terrainBlock->getShape().intersects(movedRect)) {
                const auto intersectDirection = whichDirectionIsTerrainBlock(*terrainBlock);
                if (intersectDirection == RIGHT || intersectDirection == LEFT) {
                    m_velocity.x = 0.0f;
                    return;
                }
            }
        }
        m_shape.move(dt * m_velocity);
    } else {
        assert(m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::ABOVE);
        unSnap();
    }
}

void Model::Physics::IntersectableObject::updateSnappedVertical(float dt,
                                                                const Model::Entities::Level &level,
                                                                const Constants &constants) {

    checkAndHandlePressedIntoWall(dt, constants);

    m_velocity.x = 0.0f;

    const auto movedRect = Model::Shape::Rectangle(m_shape).shrink(1.f) + dt * m_velocity;
    for (const auto &terrainBlock : level.getTerrainBlocks()) {
        if (terrainBlock->getShape().intersects(movedRect)) {
            const auto intersectDirection = whichDirectionIsTerrainBlock(*terrainBlock);
            if (intersectDirection == WHERE_IS_SNAPPED_TERRAIN::BELOW) {
                m_velocity.y = 0.0f;
                return;
            }
        }
    }

    m_shape.move(dt * m_velocity);
}

void Model::Physics::IntersectableObject::checkAndHandlePressedIntoWall(float dt,
                                                                        const Model::Physics::Constants &constants) {
    assert(m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::RIGHT ||
           m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::LEFT);

    const auto movedRect = m_shape + m_shape.width * 0.5f *
                                     Model::Shape::Point{
                                             m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::RIGHT ? 1.0f : -1.0f,
                                             0.0f
                                     };

    if (not m_snappedTerrainBlock.get().getShape().intersects(movedRect)) {
        unSnap();
    }
    bool isPressingIntoWall = (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::RIGHT && m_velocity.x > 0.0f) ||
                              (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::LEFT && m_velocity.x < 0.0f);
    applyGravity(dt, constants);
    if (isPressingIntoWall) {
        m_velocity.x = 0.0f;
    }
}

void Model::Physics::IntersectableObject::unSnap() {
    m_snappedTerrainBlock.set(nullptr);
}
