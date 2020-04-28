//
// Created by pc on 4/27/20.
//

#ifndef SFML_DEATHTIMER_H
#define SFML_DEATHTIMER_H

#include "finiteduration.h"

#include <SFML/System/Clock.hpp>

namespace Model {
    namespace Physics {

        class DeathTimer : public FiniteDuration {

        public:
            explicit DeathTimer(const float deathTime = 1.0f);

            bool shouldClean() const override;

        private:
            const float m_deathTime;
            sf::Clock m_clock;
        };
    } // namespace Physics
} // namespace Model
#endif // SFML_DEATHTIMER_H
