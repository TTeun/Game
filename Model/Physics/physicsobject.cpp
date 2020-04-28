//
// Created by pc on 4/28/20.
//

#include "physicsobject.h"

namespace Physics {

    void PhysicsObject::setVelocity(const sf::Vector2f & velocity)
    {
        m_velocity = velocity;
    }

    const sf::Vector2f & PhysicsObject::getVelocity() const
    {
        return m_velocity;
    }

    void PhysicsObject::update(float dt, const Physics::Constants & constants)
    {
        m_shape.move(dt * m_velocity);
        applyGravity(dt, constants);
    }

    void PhysicsObject::setFeelsGravity(bool feelsGravity)
    {
        m_feelsGravity = feelsGravity;
    }
    void PhysicsObject::addForce(float dt, const sf::Vector2f & force)
    {
        m_velocity += dt * force / m_mass;
    }
    PhysicsObject::PhysicsObject(Rectangle && shape) : Object(std::move(shape))
    {
    }
    PhysicsObject::PhysicsObject(Rectangle && shape, const sf::Vector2f & velocity)
        : Object(std::move(shape)), m_velocity(velocity)
    {
    }
    void PhysicsObject::applyGravity(float dt, const Constants & constants)
    {
        if (m_feelsGravity) {
            m_velocity.y += dt * constants.m_gravitationalConstant;
            if (m_velocity.y > constants.m_maxVerticalSpeed) {
                m_velocity.y = constants.m_maxVerticalSpeed;
            }
        }
    }

} // namespace Physics