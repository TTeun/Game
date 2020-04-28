//
// Created by pc on 4/26/20.
//

#ifndef SFML_DEBRISEXPLOSION_H
#define SFML_DEBRISEXPLOSION_H

#include "debris.h"

#include <list>

namespace Model {

    namespace Entities {

        class Level;

        class DebrisExplosion : Physics::FiniteDuration {

        public:
            DebrisExplosion(const sf::Vector2f & position, size_t count);

            const std::list<Debris> & getDebrisVector() const;

            void update(float dt, const Level & terrain, const Physics::Constants & constants);

            bool shouldClean() const;

        private:
            std::list<Debris> m_debrisVector;
        };
    } // namespace Entities
} // namespace Model
#endif // SFML_DEBRISEXPLOSION_H
