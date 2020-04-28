//
// Created by pc on 4/27/20.
//

#include "enemy.h"

Entities::Enemy::Enemy(const sf::Vector2f & size, const sf::Vector2f & position)
    : Physics::IntersectableObject(Rectangle(size, position))
{
    setFeelsGravity(false);
    m_mass = 1;
}
