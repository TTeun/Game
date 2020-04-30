//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_PHYSICSOBJECT_H
#define TEUN_GAME_PHYSICSOBJECT_H

#include "constants.h"
#include "object.h"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Window.hpp>

namespace Model {

    namespace Physics {

        class PhysicsObject : public Object {

        public:
            explicit PhysicsObject(Model::Shape::Rectangle &&shape);

            void setVelocity(const sf::Vector2f &velocity);

            const sf::Vector2f &getVelocity() const;

            void update(float dt, const Constants &constants);

            void addForce(float dt, const sf::Vector2f &force);

            void setFeelsGravity(bool feelsGravity);

        protected:
            void applyGravity(float dt, const Constants &constants);

            sf::Vector2f m_velocity;

            float m_mass = 1.0f;

            bool m_feelsGravity = true;
        };

    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_PHYSICSOBJECT_H
