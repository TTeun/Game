//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_KEYBOARDHANDLER_H
#define TEUN_GAME_KEYBOARDHANDLER_H

#include "keystate.h"

#include <vector>

namespace View {
    class Window;
}

class Game;

namespace Controller {
    class KeyBoardHandler {

    public:
        KeyBoardHandler();

        void handleKeyInput(Game &game);

    private:
        void handleKeyRelease(Game &game, const sf::Keyboard::Key &key);

        void handleKeyPress(Game &game, const sf::Keyboard::Key &key);

        std::vector<KeyState> m_keyStates;
    };

} // namespace Controller

#endif // TEUN_GAME_KEYBOARDHANDLER_H
