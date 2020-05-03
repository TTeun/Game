//
// Created by pc on 4/27/20.
//

#include "enemy.h"

#include "../../View/drawinterface.h"

Model::Entities::Enemy::Enemy(const sf::Vector2f & size, const Geometry::Point & position)
    : Physics::IntersectableObject(Model::Geometry::ColoredRectangle(size, position))
{
    setFeelsGravity(false);
    m_mass = 1;
}

Model::Entities::Enemy Model::Entities::Enemy::create(const Geometry::Point & position)
{
    auto enemy = Model::Entities::Enemy({20, 20}, position);
    enemy.m_shape.setColor(sf::Color::Yellow);
    enemy.setMaxVelocity(350.0f);
    return enemy;
}

void Model::Entities::Enemy::handleAi(float dt, const Model::Entities::EntityController & entityController)
{
}

void Model::Entities::Enemy::draw(View::Window & window) const
{
    View::DrawInterface::draw(*this, window);
}
