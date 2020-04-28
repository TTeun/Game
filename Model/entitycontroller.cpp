//
// Created by pc on 4/26/20.
//

#include "entitycontroller.h"

#include <iostream>

Model::EntityController::EntityController() : m_level(new Entities::Level())
{
    addEnemy({200, 200});
    addEnemy({270, 501});
    addEnemy({201, 920});
}

const Model::Entities::Player & Model::EntityController::getPlayer() const
{
    return m_player;
}

const std::list<Model::Entities::DebrisExplosion> & Model::EntityController::getDebrisExplosions() const
{
    return m_debrisExplosionVector;
}

void Model::EntityController::handleAi(float dt, const DataStructures::RectGraph & rectGraph)
{
    for (auto & enemy : m_enemyVector) {
        auto vel           = rectGraph.findDirectionToTarget(enemy.getShape(), getLevel(), 0.9f);
        const float length = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        vel /= length;
        enemy.setVelocity(dt * vel * 200000.f);
    }
}

void Model::EntityController::update(float dt, const Physics::Constants & constants)
{
    if (dt == 0) {
        std::cout << "dt == 0 ???? \n";
    }
    for (auto & explosion : m_debrisExplosionVector) {
        explosion.update(dt, *m_level, constants);
    }
    for (auto & enemy : m_enemyVector) {
        enemy.update(dt, *m_level, constants);
    }
    for (auto it = m_debrisExplosionVector.begin(); it != m_debrisExplosionVector.end();) {
        if (it->shouldClean()) {
            it = m_debrisExplosionVector.erase(it);
        } else {
            ++it;
        }
    }
    m_player.update(dt, *m_level, constants);
}

const Model::Entities::Level & Model::EntityController::getLevel() const
{
    return *m_level;
}

Model::Entities::Player & Model::EntityController::getPlayer()
{
    return m_player;
}

void Model::EntityController::addDebrisExplosion()
{
    m_debrisExplosionVector.emplace_back(m_player.getShape().getPosition() + 0.5f * m_player.getShape().getSize(), 12);
}

void Model::EntityController::setLevel(std::unique_ptr<Entities::Level> level)
{
    m_level = std::move(level);
}

const std::list<Model::Entities::Enemy> & Model::EntityController::getEnemies() const
{
    return m_enemyVector;
}

void Model::EntityController::addEnemy(const sf::Vector2f & position)
{
    m_enemyVector.emplace_back(Entities::Enemy::create(position));
}
