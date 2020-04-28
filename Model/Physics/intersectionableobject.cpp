//
// Created by pc on 4/28/20.
//

#include "intersectableobject.h"

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
        const auto movedRect = Rectangle(m_shape).shrink(0.99) + dt * m_velocity;

        for (const auto & terrainBlock : level.getTerrainBlocks()) {
            if (terrainBlock->getShape().intersects(movedRect)) {
                m_velocity = {0.0f, 0.0f};
                break;
            }
        }
        m_shape.move(dt * m_velocity);

        applyGravity(dt, constants);*
    }

} // namespace Physics