//
// Created by pc on 4/26/20.
//

#include "entitycontroller.h"

#include <iostream>

Model::EntityController::EntityController() : m_levelWrapper(new Entities::LevelWrapper()),
                                              m_water(new Water(Model::Shape::Rectangle({0.f, 500.f, 200.f, 200.f},
                                                                                        sf::Color::Blue))) {
    addEnemy({200, 200});
    addEnemy({270, 501});
    addEnemy({201, 920});
}

const Model::Entities::Player &Model::EntityController::getPlayer() const {
    return m_player;
}

const std::list<Model::Entities::DebrisExplosion> &Model::EntityController::getDebrisExplosions() const {
    return m_debrisExplosionVector;
}

void Model::EntityController::handleAi(float dt, const DataStructures::RectGraph &rectGraph) {
    for (auto &enemy : m_enemyVector) {
        auto vel = rectGraph.findDirectionToTarget(enemy.getShape(), getLevelWrapper(), 0.9f);
        const float length = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        vel /= length;
//        enemy.setVelocity(enemy.getVelocity() + dt * vel * 200.f);
        enemy.setVelocity(vel * 60.f);
    }
}

void Model::EntityController::update(float dt, const Physics::Constants &constants) {
    if (dt == 0) {
        std::cout << "dt == 0 ???? \n";
    }
    m_water->update(dt, static_cast<const Model::Entities::LevelWrapper *>( m_levelWrapper.get())->getLevel(),
                    constants);
    for (auto &explosion : m_debrisExplosionVector) {
        explosion.update(dt, static_cast<const Model::Entities::LevelWrapper *>( m_levelWrapper.get())->getLevel(),
                         constants);
    }
    for (auto &enemy : m_enemyVector) {
        enemy.update(dt, static_cast<const Model::Entities::LevelWrapper *>( m_levelWrapper.get())->getLevel(),
                     constants);
    }
    for (auto it = m_debrisExplosionVector.begin(); it != m_debrisExplosionVector.end();) {
        if (it->shouldClean()) {
            it = m_debrisExplosionVector.erase(it);
        } else {
            ++it;
        }
    }
    m_player.update(dt, static_cast<const Model::Entities::LevelWrapper *>( m_levelWrapper.get())->getLevel(),
                    constants);
}

const Model::Entities::LevelWrapper &Model::EntityController::getLevelWrapper() const {
    return *m_levelWrapper;
}

Model::Entities::Player &Model::EntityController::getPlayer() {
    return m_player;
}

void Model::EntityController::addDebrisExplosion() {
    m_debrisExplosionVector.emplace_back(m_player.getShape().getPosition() + 0.5f * m_player.getShape().getSize(), 12);
}

void Model::EntityController::setLevel(std::unique_ptr<Entities::Level> level) {
    m_levelWrapper->initLevelWrapperWithLevel(std::move(level));
}

const std::list<Model::Entities::Enemy> &Model::EntityController::getEnemies() const {
    return m_enemyVector;
}

void Model::EntityController::addEnemy(const sf::Vector2f &position) {
    m_enemyVector.emplace_back(Entities::Enemy::create(position));
}

const Water &Model::EntityController::getWater() const {
    return *m_water;
}
