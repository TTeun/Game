//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_PHYSICSOBJECT_H
#define TEUN_GAME_PHYSICSOBJECT_H

#include "object.h"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Window.hpp>

namespace Model {

    namespace Physics {

        class Constants;

        class PhysicsObject : public Object {

        public:
            explicit PhysicsObject(Geometry::ColoredRectangle && shape);

            void setVelocity(const Geometry::Vector2d & velocity);

            const Geometry::Vector2d & getVelocity() const;

            void update(float dt, const Constants & constants);

            void addForce(float dt, const Geometry::Vector2d & force);

            void setFeelsGravity(bool feelsGravity);

        protected:
            void applyGravity(float dt, const Constants & constants);

            Model::Geometry::Vector2d m_velocity;

            float m_mass = 1.0f;

            bool m_feelsGravity = true;
        };

    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_PHYSICSOBJECT_H
