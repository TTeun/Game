//
// Created by pc on 4/27/20.
//

#include "game.h"

#include "Model/Loaders/levelloader.h"

Game::Game()
    : m_window(new View::Window(800, 600, "Game")),
      m_drawInterface(new View::DrawInterface),
      m_model(new Model::Model()),
      m_keyBoardHandler(new Controller::KeyBoardHandler),
      m_constants(Physics::Constants::readIniFile())
{
    m_window->setShowFrameRate(true);
}

void Game::init()
{
    srand(static_cast<unsigned int>(time(0)));
    Model::Loaders::loadLevel("../Assets/Levels/level1.xml", *this);
}

void Game::play()
{
    while (m_window->isOpen()) {
        sf::Event event{};
        while (m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: m_window->close(); break;
                case sf::Event::Resized: {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    m_window->setView(sf::View(visibleArea));
                } break;
                default: break;
            }
        }

        m_window->clear(Colors::windowClearColor);

        m_keyBoardHandler->handleKeyInput(*this);
        if (not m_isPaused) {
            m_model->Entities::EntityList::update(m_window->getDtInSeconds(), *m_constants);
            //            const auto cornerRectGraph =
            //            m_model->Entities::EntityList::getLevel().getCornerRectGraphWithPlayer(
            //                40, 40, m_model->Entities::EntityList::getPlayer());
            //            cornerRectGraph.draw(*m_window);
            //
            //            m_model->Entities::EntityList::handleAi(m_window->getDtInSeconds(), cornerRectGraph);
        }
        m_window->drawModel(*m_model, getDrawInterface());

        m_window->display();
    }
}

Model::Model & Game::getModel()
{
    return *m_model;
}

void Game::reset()
{
    m_model = std::make_unique<Model::Model>();
    m_constants.reset(Physics::Constants::readIniFile());
    Model::Loaders::loadLevel("../Assets/Levels/level1.xml", *this);
}

void Game::togglePause()
{
    m_isPaused = not m_isPaused;
}

View::Window & Game::getWindow()
{
    return *m_window;
}

const Physics::Constants & Game::getConstants() const
{
    return *m_constants;
}

View::DrawInterface & Game::getDrawInterface()
{
    return *m_drawInterface;
}
