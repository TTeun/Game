//
// Created by pc on 4/26/20.
//

#ifndef SFML_PHYSICSOBJECT_H
#define SFML_PHYSICSOBJECT_H

#include "constants.h"
#include "object.h"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Window.hpp>

namespace Physics {

    template <class T>
    class PhysicsObject : public Object<T> {

    public:
        PhysicsObject(T && shape, const sf::Vector2f & velocity) : Object<T>(std::move(shape)), m_velocity(velocity)
        {
        }

        explicit PhysicsObject(T && shape) : Object<T>(std::move(shape))
        {
        }

        void setVelocity(const sf::Vector2f & velocity);

        const sf::Vector2f & getVelocity() const
        {
            return m_velocity;
        }

        void update(float dt, const Constants & constants);

        void addForce(float dt, const sf::Vector2f & force)
        {
            m_velocity += dt * force / m_mass;
        }

        void setFeelsGravity(bool feelsGravity)
        {
            m_feelsGravity = feelsGravity;
        }

    protected:
        sf::Vector2f m_velocity;

        float m_mass = 1.0f;

        bool m_feelsGravity = true;
    };

    template <class T>
    void PhysicsObject<T>::setVelocity(const sf::Vector2f & velocity)
    {
        m_velocity = velocity;
    }

    template <class T>
    void PhysicsObject<T>::update(float dt, const Physics::Constants & constants)
    {
        m_velocity.y += constants.m_gravitationalConstant * dt;
        Object<T>::m_shape.move(dt * m_velocity);
    }

} // namespace Physics

#endif // SFML_PHYSICSOBJECT_H
