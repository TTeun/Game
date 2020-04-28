//
// Created by pc on 4/27/20.
//

#ifndef SFML_KEYSTATE_H
#define SFML_KEYSTATE_H

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Controller {

    class KeyState {
        friend class KeyBoardHandler;

        enum Behaviour { DISABLE_UNTIL_RELEASE, ALWAYS_FIRE };

        enum KeyEventType { NEW_PRESS, RELEASED, HELD_DOWN, NONE };

    public:
        KeyState(Behaviour Behaviour, sf::Keyboard::Key Key, float resetTime = 0.001f);

    private:
        KeyEventType update(bool keyIsPressed);

        const sf::Keyboard::Key & getKey() const;

        const float m_resetTime = 0.0f;
        sf::Clock m_clock;
        Behaviour m_behaviour;
        bool m_isPressed = false;
        sf::Keyboard::Key m_key;
    };

} // namespace Controller

#endif // SFML_KEYSTATE_H
