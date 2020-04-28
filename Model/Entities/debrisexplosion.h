//
// Created by pc on 4/26/20.
//

#ifndef SFML_DEBRISEXPLOSION_H
#define SFML_DEBRISEXPLOSION_H

#include "debris.h"

#include <list>

namespace Entities {

    class Level;

    class DebrisExplosion : Physics::FiniteDuration {

    public:
        DebrisExplosion(const sf::Vector2f & position,
                        size_t count,
                        const sf::Color & color,
                        const sf::Color & outlineColor,
                        const Uniform & sizeUniform,
                        const Uniform & directionUniform,
                        const Uniform & numberOfPointsUniform);

        const std::list<Debris> & getDebrisVector() const;

        void update(float dt, const Level & terrain, const Physics::Constants & constants);

        bool shouldClean() const;

    private:
        std::list<Debris> m_debrisVector;
    };
} // namespace Entities

#endif // SFML_DEBRISEXPLOSION_H
