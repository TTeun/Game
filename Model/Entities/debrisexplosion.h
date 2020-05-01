//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_DEBRISEXPLOSION_H
#define TEUN_GAME_DEBRISEXPLOSION_H

#include "debris.h"

#include <list>

namespace Model {

    namespace Entities {

        class Level;

    class DebrisExplosion : Physics::FiniteDuration, public View::Drawable {

        public:
            DebrisExplosion(const sf::Vector2f &position, size_t count);

        void draw(View::Window &window) const override;

        const std::list<Debris> &getDebrisVector() const;

            void update(float dt, const Level &level, const Physics::Constants &constants);

            bool shouldClean() const;

        private:
            std::list<Debris> m_debrisVector;
        };
    } // namespace Entities
} // namespace Model
#endif // TEUN_GAME_DEBRISEXPLOSION_H
