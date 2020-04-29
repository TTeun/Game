#include "game.h"

#include "Model/Loaders/levelloader.h"

Game::Game()
        : m_window(new View::Window(800, 600, "Game")),
          m_drawInterface(new View::DrawInterface),
          m_entityController(new Model::EntityController()),
          m_keyBoardHandler(new Controller::KeyBoardHandler),
          m_constants(Model::Physics::Constants::readIniFile()) {
    m_window->setShowFrameRate(true);
}

void Game::init() {
    srand(static_cast<unsigned int>(time(0)));
    Model::Loaders::loadLevel("../Assets/Levels/level1.xml", *this);
}

void Game::play() {
    while (m_window->isOpen()) {
        handlePolledEvents(*m_window);
        m_keyBoardHandler->handleKeyInput(*this);

        m_window->clear(Colors::windowClearColor);
        if (not m_isPaused) {
            m_entityController->update(m_window->getDtInSeconds(), *m_constants);

            const auto cornerRectGraph = m_entityController->getLevelWrapper().buildCornerRectGraphWithPlayer(
                    40, 40, static_cast<const Model::EntityController *>(m_entityController.get())->getPlayer()
            );
            cornerRectGraph.draw(*m_window);

//            m_entityController->handleAi(m_window->getDtInSeconds(), cornerRectGraph);
        }
        m_window->drawModel(*m_entityController, getDrawInterface());

        m_window->display();
    }
}

Model::EntityController &Game::getModel() {
    return *m_entityController;
}

void Game::reset() {
    m_entityController = std::make_unique<Model::EntityController>();
    m_constants = Model::Physics::Constants::readIniFile();
    Model::Loaders::loadLevel("../Assets/Levels/level1.xml", *this);
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
