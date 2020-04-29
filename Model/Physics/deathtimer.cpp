//
// Created by pc on 4/27/20.
//

#include "deathtimer.h"

Model::Physics::DeathTimer::DeathTimer(const float deathTime) : m_deathTime(deathTime) {
    m_clock.restart();
}

bool Model::Physics::DeathTimer::shouldClean() const {
    return m_clock.getElapsedTime().asSeconds() >= m_deathTime;
}

std::ostream &Model::Physics::operator<<(std::ostream &os, const Model::Physics::DeathTimer &timer) {
    os << static_cast<const FiniteDuration &>(timer) << " m_deathTime: " << timer.m_deathTime
       << " m_clock.getElapsed().asSeconds(): "
       << timer.m_clock.getElapsedTime().asSeconds();
    return os;
}
