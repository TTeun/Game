//
// Created by pc on 4/26/20.
//

#ifndef SFML_INTERSECTABLEOBJECT_H
#define SFML_INTERSECTABLEOBJECT_H

#include "../../Aux/shapetools.h"
#include "../Entities/level.h"
#include "intersectioninfo.h"
#include "intersector.h"
#include "physicsobject.h"

#include <cmath>
#include <iostream>

namespace Physics {

    template <class T>
    class IntersectableObject : public PhysicsObject<T> {

    public:
        IntersectableObject(T && shape, const sf::Vector2f & velocity) : PhysicsObject<T>(std::move(shape), velocity)
        {
        }

        explicit IntersectableObject(T && shape) : PhysicsObject<T>(std::move(shape))
        {
        }

        virtual void update(float dt, const Entities::Level & terrain, const Physics::Constants & constants)
        {
            if (m_isGrounded && Physics::PhysicsObject<T>::m_feelsGravity) {
                updateGrounded(dt, terrain, constants);
            } else {
                updateNotGrounded(dt, terrain, constants);
            }
        }

    protected:
        void updateGrounded(float dt, const Entities::Level & terrain, const Physics::Constants & constants)
        {
            if (std::abs(PhysicsObject<T>::m_velocity.x) > constants.m_maxHorizontalSpeed) {
                PhysicsObject<T>::m_velocity.x =
                    (PhysicsObject<T>::m_velocity.x > 0.0f ? 1.0f : (-1.0f)) * constants.m_maxHorizontalSpeed;
            }
            PhysicsObject<T>::m_velocity.x *= pow(constants.m_surfaceFriction, dt);
            if (std::abs(PhysicsObject<T>::m_velocity.x) <= 1) {
                PhysicsObject<T>::m_velocity.x = 0.0f;
            }
            const auto & terrainBlocks = terrain.getTerrainBlocks();
            IntersectionInfo info;
            for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
                info.update(intersect(*this, **it, dt));
            }
            handleHorizontalIntersection(info, dt);
            if (not isGrounded(terrain)) {
                m_isGrounded = false;
            }
        }

        virtual void updateNotGrounded(float dt, const Entities::Level & terrain, const Physics::Constants & constants)
        {
            if (Physics::PhysicsObject<T>::m_feelsGravity) {
                PhysicsObject<T>::m_velocity.y += constants.m_gravitationalConstant * dt;
            }
            IntersectionInfo info;
            const auto & terrainBlocks = terrain.getTerrainBlocks();
            for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
                info.update(intersect(*this, **it, dt));
            }
            if (info.type() == IntersectionInfo::Type::None) {
                Object<T>::m_shape.move(dt * PhysicsObject<T>::m_velocity);
            } else {
                handlePossibleIntersection(info, dt);
            }
        }

        bool isGrounded(const Entities::Level & terrain)
        {
            sf::FloatRect rect = ShapeTools::getBoundingRectangle(this->getShape());
            rect.top += 1;
            const auto & terrainBlocks = terrain.getTerrainBlocks();
            for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
                ;
                if (rect.intersects(ShapeTools::getBoundingRectangle((*it)->getShape()))) {
                    return true;
                }
            }
            return false;
        }

        void moveHorizontally(bool isStuckToSurface, float dt, float s)
        {
            if (isStuckToSurface) {
                Object<T>::m_shape.move({dt * PhysicsObject<T>::m_velocity.x, 0.0f});
            } else {
                Object<T>::m_shape.move({s * dt * PhysicsObject<T>::m_velocity.x, 0.0f});
                PhysicsObject<T>::m_velocity.x = 0.0f;
            }
        }

        void moveVertically(bool isStuckToSurface, float dt, float s)
        {
            if (isStuckToSurface) {
                Object<T>::m_shape.move({0.0f, dt * PhysicsObject<T>::m_velocity.y});
            } else {
                Object<T>::m_shape.move({0.0, s * dt * PhysicsObject<T>::m_velocity.y});
                PhysicsObject<T>::m_velocity.y = 0.0f;
            }
        }

        virtual void handleHorizontalIntersection(const IntersectionInfo & info, float dt)
        {
            const auto horizontalIntersection = info.horizontalIntersection();
            switch (horizontalIntersection.second) {
                case IntersectionInfo::Type::None:
                    Object<T>::m_shape.move(sf::Vector2f(dt * PhysicsObject<T>::m_velocity.x, 0));
                    break;
                case IntersectionInfo::Type::LeftToRight:

                    moveHorizontally(PhysicsObject<T>::m_velocity.x < 0, dt, horizontalIntersection.first);
                    break;
                case IntersectionInfo::Type::RightToLeft:
                    moveHorizontally(PhysicsObject<T>::m_velocity.x > 0, dt, horizontalIntersection.first);
                    break;
                default: std::cout << "Rare horizontal intersection\n";
            }
        }

        void handleVerticalIntersection(const IntersectionInfo & info, float dt)
        {
            const auto verticalIntersection = info.verticalIntersection();
            switch (verticalIntersection.second) {
                case IntersectionInfo::Type::None:
                    Object<T>::m_shape.move(sf::Vector2f(0, dt * PhysicsObject<T>::m_velocity.y));
                    break;
                case IntersectionInfo::Type::TopToBottom: {
                    bool isStuckToSurface = PhysicsObject<T>::m_velocity.y < 0;
                    moveVertically(isStuckToSurface, dt, verticalIntersection.first);
                    if (not isStuckToSurface) {
                        m_isGrounded = true;
                    }
                } break;
                case IntersectionInfo::Type::BottomToTop:
                    moveVertically(PhysicsObject<T>::m_velocity.y > 0, dt, verticalIntersection.first);
                    break;
                default: std::cout << "Rare vertical intersection\n";
            }
        }

        void handlePossibleIntersection(const IntersectionInfo & info, float dt)
        {
            handleHorizontalIntersection(info, dt);
            handleVerticalIntersection(info, dt);
        }

    protected:
        bool m_isGrounded = false;
    };

} // namespace Physics

#endif // SFML_INTERSECTABLEOBJECT_H
