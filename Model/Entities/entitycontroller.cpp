//
// Created by pc on 4/26/20.
//

#include "entitycontroller.h"

#include "../../View/drawinterface.h"

#include <iostream>
#include <memory>

Model::Entities::EntityController::EntityController()
    : m_levelWrapper(new Entities::LevelWrapper()),
      m_water(new Water(Model::Geometry::Rectangle({-300.f, 500.f, 400.f, 400.f})))
{
    addEnemy({200, 200});
    addEnemy({270, 501});
    addEnemy({201, 920});
}

const Model::Entities::Player & Model::Entities::EntityController::getPlayer() const
{
    assert(m_player);
    return *m_player;
}

const std::list<Model::Entities::DebrisExplosion> & Model::Entities::EntityController::getDebrisExplosions() const
{
    return m_debrisExplosionVector;
}

void Model::Entities::EntityController::handleAi(float dt)
{
    for (auto & enemy : m_enemyVector) {
        auto vel =
            getLevelWrapper().getCornerRectGraph().findDirectionToTarget(enemy.getShape(), getLevelWrapper(), 1.0f);
        const float length = vel.getLength();
        vel /= length != 0 ? length : 1.0f;
        //        enemy.setVelocity(vel * 100.f);
        enemy.addForce(dt, 500.0f * vel);
    }
}

void Model::Entities::EntityController::update(float dt, const Physics::Constants & constants)
{
    if (dt == 0) {
        std::cout << "dt == 0 ???? \n";
    }
    m_water->update(
        dt, static_cast<const Model::Entities::LevelWrapper *>(m_levelWrapper.get())->getLevel(), constants);
    for (auto & explosion : m_debrisExplosionVector) {
        explosion.update(
            dt, static_cast<const Model::Entities::LevelWrapper *>(m_levelWrapper.get())->getLevel(), constants);
    }
    getPlayer().update(
        dt, static_cast<const Model::Entities::LevelWrapper *>(m_levelWrapper.get())->getLevel(), constants);

    getLevelWrapper().addPlayerToCornerRectGraph(getPlayer());

    for (auto & enemy : m_enemyVector) {
        enemy.update(
            dt, static_cast<const Model::Entities::LevelWrapper *>(m_levelWrapper.get())->getLevel(), constants);
    }
    for (auto it = m_debrisExplosionVector.begin(); it != m_debrisExplosionVector.end();) {
        if (it->shouldClean()) {
            it = m_debrisExplosionVector.erase(it);
        } else {
            ++it;
        }
    }
}

const Model::Entities::LevelWrapper & Model::Entities::EntityController::getLevelWrapper() const
{
    assert(m_levelWrapper);
    return *m_levelWrapper;
}

Model::Entities::Player & Model::Entities::EntityController::getPlayer()
{
    assert(m_player);
    return *m_player;
}

void Model::Entities::EntityController::addDebrisExplosion()
{
    m_debrisExplosionVector.emplace_back(getPlayer().getShape().getPosition() + 0.5f * getPlayer().getShape().getSize(),
                                         12);
}

void Model::Entities::EntityController::setLevel(std::unique_ptr<Entities::Level> level)
{
    m_levelWrapper->initLevelWrapperWithLevel(std::move(level));
}

const std::list<Model::Entities::Enemy> & Model::Entities::EntityController::getEnemies() const
{
    return m_enemyVector;
}

void Model::Entities::EntityController::addEnemy(const Geometry::Point & position)
{
    m_enemyVector.emplace_back(Entities::Enemy::create(position));
}

const Model::Entities::Water & Model::Entities::EntityController::getWater() const
{
    assert(m_water);
    return *m_water;
}

void Model::Entities::EntityController::addPlayer(float x, float y, float width, float height, const sf::Color & color)
{
    m_player = std::make_unique<Model::Entities::Player>(x, y, width, height, 1400.0f, color);
}

Model::Entities::LevelWrapper & Model::Entities::EntityController::getLevelWrapper()
{
    return *m_levelWrapper;
}

void Model::Entities::EntityController::draw(View::Window & window) const
{
    View::DrawInterface::draw(*this, window);
}
