//
// Created by pc on 4/27/20.
//

#include "enemy.h"

#include "../../View/drawinterface.h"

Model::Entities::Enemy::Enemy(const sf::Vector2f &size, const sf::Vector2f &position)
        : Physics::IntersectableObject(Model::Shapes::ColoredRectangle(size, position)) {
    setFeelsGravity(false);
    m_mass = 1;
}

Model::Entities::Enemy Model::Entities::Enemy::create(const sf::Vector2f &position) {
    auto enemy = Model::Entities::Enemy({20, 20}, position);
    enemy.m_shape.setColor(sf::Color::Yellow);
    return enemy;
}

void Model::Entities::Enemy::handleAi(float dt, const Model::Entities::EntityController &entityController) {

}

void Model::Entities::Enemy::draw(View::Window &window) const {
    View::DrawInterface::draw(*this, window);
}
