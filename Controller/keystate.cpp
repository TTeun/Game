//
// Created by pc on 4/27/20.
//

#include "keystate.h"

Controller::KeyState::KeyState(Controller::KeyState::BEHAVIOUR behaviour, sf::Keyboard::Key key, float resetTime)
        : m_resetTime(resetTime), m_behaviour(behaviour), m_key(key) {
    m_clock.restart();
}

Controller::KeyState::KEY_EVENT_TYPE Controller::KeyState::update(bool keyIsPressed) {
    if (keyIsPressed && m_isPressed) {
        if (m_resetTime != 0.0f) {
            if (m_clock.getElapsedTime().asSeconds() >= m_resetTime) {
                m_clock.restart();
                return NEW_PRESS;
            }
        }
        return HELD_DOWN;
    } else if (keyIsPressed) {
        m_clock.restart();
        m_isPressed = true;
        return NEW_PRESS;
    } else if (m_isPressed) {
        m_isPressed = false;
        return RELEASED;
    } else {
        return NONE;
    }
}

const sf::Keyboard::Key &Controller::KeyState::getKey() const {
    return m_key;
}
