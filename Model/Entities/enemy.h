//
// Created by pc on 4/27/20.
//

#ifndef SFML_ENEMY_H
#define SFML_ENEMY_H

#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Entities {
    class Enemy : public Physics::IntersectableObject<Rectangle> {

    public:
        Enemy(const sf::Vector2f & size, const sf::Vector2f & position)
            : Physics::IntersectableObject<Rectangle>(Rectangle(size, position))
        {
            setFeelsGravity(false);
            m_mass = 0.2;
        }

    private:
    };
} // namespace Entities

#endif // SFML_ENEMY_H
