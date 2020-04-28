//
// Created by pc on 4/26/20.
//

#include "entitylist.h"

#include "../../Aux/uniform.h"

Entities::EntityList::EntityList() : m_level(new Level())
{
    addEnemy(sf::Vector2f(20.0f, 20.0f), {200, 200});
    addEnemy(sf::Vector2f(20.0f, 20.0f), {270, 501});
    addEnemy(sf::Vector2f(20.0f, 20.0f), {201, 920});
}

const Entities::Player & Entities::EntityList::getPlayer() const
{
    return m_player;
}

const std::list<Entities::DebrisExplosion> & Entities::EntityList::getDebrisExplosions() const
{
    return m_debrisExplosionVector;
}

void Entities::EntityList::handleAi(float dt, const RectGraph & rectGraph)
{
    for (auto & enemy : m_enemyVector) {
        auto vel           = rectGraph.findDirectionToTarget(enemy.getShape(), getLevel(), 0.9f);
        const float length = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        vel /= length;
        enemy.setVelocity(dt * vel * 20000.f);
    }
}

void Entities::EntityList::update(float dt, const Physics::Constants & constants)
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

const Entities::Level & Entities::EntityList::getLevel() const
{
    return *m_level;
}

Entities::Player & Entities::EntityList::getPlayer()
{
    return m_player;
}

void Entities::EntityList::addDebrisExplosion()
{
    m_debrisExplosionVector.emplace_back(m_player.getShape().getPosition() + 0.5f * m_player.getShape().getSize(),
                                         12,
                                         Colors::playerColor,
                                         Colors::outlineColor,
                                         Uniform(5, 3),
                                         Uniform(99, 5),
                                         Uniform(4, 2));
}

void Entities::EntityList::setLevel(Entities::Level * level)
{
    m_level.reset(level);
}

const std::list<Entities::Enemy> & Entities::EntityList::getEnemies() const
{
    return m_enemyVector;
}

void Entities::EntityList::addEnemy(const sf::Vector2f & size, const sf::Vector2f & position)
{
    m_enemyVector.emplace_back(Enemy(size, position));
}
