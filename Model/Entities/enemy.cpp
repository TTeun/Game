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

Entities::Enemy Entities::Enemy::create(const sf::Vector2f & position)
{
    auto enemy = Entities::Enemy({20, 20}, position);
    enemy.m_shape.setColor(sf::Color::Yellow);
    return enemy;
}
