//
// Created by pc on 4/27/20.
//

#ifndef SFML_ENEMY_H
#define SFML_ENEMY_H

#include "../Physics/intersectableobject.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Entities {
    class Enemy : public Physics::IntersectableObject {
    public:
        static Enemy create(const sf::Vector2f & position);

    private:
        Enemy(const sf::Vector2f & size, const sf::Vector2f & position);
    };
} // namespace Entities

#endif // SFML_ENEMY_H
