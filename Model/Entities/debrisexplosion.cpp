//
// Created by pc on 4/26/20.
//

#include "debrisexplosion.h"

Entities::DebrisExplosion::DebrisExplosion(const sf::Vector2f & position,
                                           size_t count,
                                           const sf::Color & color,
                                           const sf::Color & outlineColor,
                                           const Uniform & sizeUniform,
                                           const Uniform & directionUniform,
                                           const Uniform & numberOfPointsUniform)
{
    for (size_t i = 0; i != count; ++i) {
        m_debrisVector.emplace_back(Debris(position, sizeUniform));
    }
}

void Entities::DebrisExplosion::update(float dt, const Level & terrain, const Physics::Constants & constants)
{
    for (auto & debris : m_debrisVector) {
        debris.update(dt, terrain, constants);
    }
    for (auto it = m_debrisVector.begin(); it != m_debrisVector.end();) {
        if (it->shouldClean()) {
            it = m_debrisVector.erase(it);
        } else {
            ++it;
        }
    }
}

const std::list<Entities::Debris> & Entities::DebrisExplosion::getDebrisVector() const
{
    return m_debrisVector;
}

bool Entities::DebrisExplosion::shouldClean() const
{
    //    return false;
    return m_debrisVector.empty();
}
