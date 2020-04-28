//
// Created by pc on 4/27/20.
//

#ifndef SFML_GAME_H
#define SFML_GAME_H

#include "Controller/keyboardhandler.h"
#include "Model/Physics/constants.h"
#include "Model/model.h"
#include "View/window.h"

#include <memory>

class Game {

public:
    friend class Controller::KeyBoardHandler;

    friend class Model::Loaders;

    Game();

    void init();

    void play();

    void reset();

    void togglePause();

    const Physics::Constants & getConstants() const;

private:
    View::DrawInterface & getDrawInterface();

    Model::Model & getModel();

    View::Window & getWindow();

    std::unique_ptr<View::Window> m_window;
    std::unique_ptr<View::DrawInterface> m_drawInterface;
    std::unique_ptr<Model::Model> m_model;
    std::unique_ptr<Controller::KeyBoardHandler> m_keyBoardHandler;
    std::unique_ptr<const Physics::Constants> m_constants;

    bool m_isPaused = false;
};

#endif // SFML_GAME_H
