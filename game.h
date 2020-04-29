//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_GAME_H
#define TEUN_GAME_GAME_H

#include "Controller/keyboardhandler.h"
#include "Model/Physics/constants.h"
#include "Model/entitycontroller.h"
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

    const Model::Physics::Constants & getConstants() const;

private:
    void handlePolledEvents(View::Window & window);

    View::DrawInterface & getDrawInterface();

    Model::EntityController & getModel();

    View::Window & getWindow();

    std::unique_ptr<View::Window> m_window;
    std::unique_ptr<View::DrawInterface> m_drawInterface;
    std::unique_ptr<Model::EntityController> m_entityController;
    std::unique_ptr<Controller::KeyBoardHandler> m_keyBoardHandler;
    std::unique_ptr<const Model::Physics::Constants> m_constants;

    bool m_isPaused = false;
};

#endif // TEUN_GAME_GAME_H
