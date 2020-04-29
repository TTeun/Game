//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_DEATHTIMER_H
#define TEUN_GAME_DEATHTIMER_H

#include "finiteduration.h"

#include <SFML/System/Clock.hpp>
#include <ostream>

namespace Model {
    namespace Physics {

        class DeathTimer : public FiniteDuration {

        public:
            explicit DeathTimer(const float deathTime = 1.0f);

            bool shouldClean() const override;

            friend std::ostream &operator<<(std::ostream &os, const DeathTimer &timer);

        private:
            const float m_deathTime;
            sf::Clock m_clock;
        };
    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_DEATHTIMER_H
