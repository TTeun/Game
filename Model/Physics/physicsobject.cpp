#include "physicsobject.h"

#include "constants.h"

Model::

    Physics::PhysicsObject::PhysicsObject(Geometry::ColoredRectangle && shape)
    : Object(std::move(shape))
{
}

void Model::Physics::PhysicsObject::setVelocity(const Geometry::Vector2d & velocity)
{
    m_velocity = velocity;
}

const Model::Geometry::Vector2d & Model::Physics::PhysicsObject::getVelocity() const
{
    return m_velocity;
}

void Model::Physics::PhysicsObject::update(float dt, const Physics::Constants & constants)
{
    m_shape.move(dt * m_velocity);
    applyGravity(dt, constants);
}

void Model::Physics::PhysicsObject::setFeelsGravity(bool feelsGravity)
{
    m_feelsGravity = feelsGravity;
}

void Model::Physics::PhysicsObject::addForce(float dt, const Geometry::Vector2d & force)
{
    m_velocity += dt * force / m_mass;
}

void Model::Physics::PhysicsObject::applyGravity(float dt, const Constants & constants)
{
    if (m_feelsGravity) {
        m_velocity.y += dt * constants.m_gravitationalConstant;
        if (m_velocity.y > constants.m_maxVerticalSpeed) {
            m_velocity.y = constants.m_maxVerticalSpeed;
        }
    }
}
