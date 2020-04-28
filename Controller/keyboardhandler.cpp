//
// Created by pc on 4/27/20.
//

#include "keyboardhandler.h"

#include "../game.h"

Controller::KeyBoardHandler::KeyBoardHandler()
{
    m_keyStates.emplace_back(KeyState::Behaviour::DISABLE_UNTIL_RELEASE, sf::Keyboard::P, 0.2f);
    m_keyStates.emplace_back(KeyState::Behaviour::DISABLE_UNTIL_RELEASE, sf::Keyboard::R, 0.2f);
    m_keyStates.emplace_back(KeyState::Behaviour::DISABLE_UNTIL_RELEASE, sf::Keyboard::E, 0.002f);

    m_keyStates.emplace_back(KeyState::Behaviour::ALWAYS_FIRE, sf::Keyboard::W);
    m_keyStates.emplace_back(KeyState::Behaviour::ALWAYS_FIRE, sf::Keyboard::A);
    m_keyStates.emplace_back(KeyState::Behaviour::ALWAYS_FIRE, sf::Keyboard::D);
}

void Controller::KeyBoardHandler::handleKeyPress(Game & game, const sf::Keyboard::Key & key)
{
    auto & entityList = game.getModel();
    auto & window     = game.getWindow();

    switch (key) {
        case sf::Keyboard::P: game.togglePause(); break;
        case sf::Keyboard::R: game.reset(); break;
        case sf::Keyboard::A: entityList.m_player.addHorizontalForce(-1200 * window.getDtInSeconds()); break;
        case sf::Keyboard::D: entityList.m_player.addHorizontalForce(1200 * window.getDtInSeconds()); break;
        case sf::Keyboard::W: entityList.getPlayer().jump(game.getConstants()); break;
        case sf::Keyboard::E: entityList.addDebrisExplosion(); break;
        default: break;
    }
}

void Controller::KeyBoardHandler::handleKeyInput(Game & game)
{
    for (auto & it : m_keyStates) {
        const auto & key        = it.getKey();
        const bool keyIsPressed = sf::Keyboard::isKeyPressed(key);
        const auto eventType    = it.update(keyIsPressed);
        switch (eventType) {
            case KeyState::KeyEventType::NEW_PRESS: handleKeyPress(game, key); break;
            case KeyState::KeyEventType::RELEASED: handleKeyRelease(game, key); break;
            case KeyState::KeyEventType::HELD_DOWN:
                if (it.m_behaviour == KeyState::Behaviour::ALWAYS_FIRE) {
                    handleKeyPress(game, key);
                }
                break;
            default: break;
        }
    }
}

void Controller::KeyBoardHandler::handleKeyRelease(Game & game, const sf::Keyboard::Key & key)
{
}
