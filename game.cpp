#include "game.h"

#include <memory>

#include "Model/Loaders/levelloader.h"

Game::Game() {
    m_window = std::make_unique<View::Window>(1200, 800, "Game");

    m_drawInterface = std::make_unique<View::DrawInterface>();
    m_keyBoardHandler = std::make_unique<Controller::KeyBoardHandler>();
    m_constants = Model::Physics::Constants::create();

    init();
}

void Game::init() {
    srand(static_cast<unsigned int>(time(0)));

    m_entityController = std::make_unique<Model::Entities::EntityController>();
    m_entityController->addPlayer();

    Model::Loaders::loadLevel("../Assets/Levels/level1.xml", *this);
    m_window->setShowFrameRate(true);

}

void Game::play() {
    while (m_window->isOpen()) {
        handlePolledEvents(*m_window);
        m_keyBoardHandler->handleKeyInput(*this);

        m_window->clear(Colors::windowClearColor);
        m_entityController->getLevelWrapper().setCornerRectGraph(40, 40);
        if (not m_isPaused) {
            m_entityController->update(m_window->getDtInSeconds(), *m_constants);

            m_entityController->getLevelWrapper().getCornerRectGraph().draw(*m_window);

            m_entityController->handleAi(m_window->getDtInSeconds());
        }
        m_window->drawModel(*m_entityController, getDrawInterface());

        m_window->display();
    }
}

Model::Entities::EntityController &Game::getModel() {
    return *m_entityController;
}

void Game::reset() {
    init();
}

void Game::togglePause() {
    m_isPaused = not m_isPaused;
}

View::Window &Game::getWindow() {
    return *m_window;
}

const Model::Physics::Constants &Game::getConstants() const {
    return *m_constants;
}

View::DrawInterface &Game::getDrawInterface() {
    return *m_drawInterface;
}

void Game::handlePolledEvents(View::Window &window) {
    sf::Event event{};
    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::Resized: {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_window->setView(sf::View(visibleArea));
            }
                break;
            default:
                break;
        }
    }
}
