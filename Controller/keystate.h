//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_KEYSTATE_H
#define TEUN_GAME_KEYSTATE_H

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Controller {

    class KeyState {
        friend class KeyBoardHandler;

        enum BEHAVIOUR { DISABLE_UNTIL_RELEASE, ALWAYS_FIRE };

        enum KEY_EVENT_TYPE { NEW_PRESS, RELEASED, HELD_DOWN, NONE };

    public:
        KeyState(BEHAVIOUR behaviour, sf::Keyboard::Key key, float resetTime = 0.5f);

    private:
        KEY_EVENT_TYPE update(bool keyIsPressed);

        const sf::Keyboard::Key & getKey() const;

        const float m_resetTime = 0.0f;
        sf::Clock m_clock;
        BEHAVIOUR m_behaviour;
        bool m_isPressed = false;
        sf::Keyboard::Key m_key;
    };

} // namespace Controller

#endif // TEUN_GAME_KEYSTATE_H
