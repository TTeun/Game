//
// Created by pc on 4/26/20.
//

#include "window.h"

#include "../Model/entitycontroller.h"

#include <sstream>

View::Window::Window(uint width, uint height, const char * title, bool showFrameRate)
    : sf::RenderWindow(sf::VideoMode(width, height), title), m_showFrameRate(showFrameRate)
{
    if (!m_font.loadFromFile("../Assets/arial.ttf")) {
    }
    m_text.setFont(m_font);
    m_text.setCharacterSize(18); // in pixels, not points!
    m_text.setFillColor(sf::Color::Black);
    //        setVerticalSyncEnabled(true);
    clear(Colors::windowClearColor);
}

sf::View View::Window::calculateViewPort(const Model::Entities::Player & player)
{
    const auto position   = player.getShape().getPosition();
    const auto velocity   = player.getVelocity();
    const auto windowSize = sf::Vector2f{static_cast<float>(getSize().x), static_cast<float>(getSize().y)};

    m_viewPortPositionVelocityOffset = 0.999f * m_viewPortPositionVelocityOffset + 0.001f * velocity;
    m_viewRect = sf::FloatRect(position - 0.5f * windowSize + 0.2f * m_viewPortPositionVelocityOffset, windowSize);
    return sf::View(m_viewRect);
}

void View::Window::drawModel(const Model::EntityController & model, View::DrawInterface & drawInterface)
{
    m_dt = m_clock.getElapsedTime().asMicroseconds();
    m_clock.restart();

    drawInterface.drawModel(*this, model);

    if (m_showFrameRate) {
        m_frameRate = static_cast<float>(1000000.0 / m_dt);
        std::stringstream ss;
        ss << "fps: " << m_frameRate;
        m_text.setString(ss.str());
        m_text.setPosition(calculateViewPort(model.getPlayer()).getCenter() -
                           0.4f * sf::Vector2f{static_cast<float>(getSize().x), static_cast<float>(getSize().y)});
        draw(m_text);
    }
    setView(calculateViewPort(model.getPlayer()));
}

void View::Window::setShowFrameRate(bool showFrameRate)
{
    m_showFrameRate = showFrameRate;
}

float View::Window::getDtInSeconds() const
{
    return static_cast<float>(m_dt / 1000000.0);
}

const sf::FloatRect & View::Window::getViewRect() const
{
    return m_viewRect;
}

void View::Window::drawRectangle(float x, float y, float width, float height, const sf::Color & color)
{
    sf::RectangleShape shape({width, height});
    shape.setPosition({x, y});
    shape.setFillColor(color);
    draw(shape);
}

void View::Window::drawRectangle(const Model::Shape::Rectangle & rect)
{
    drawRectangle(rect.left, rect.top, rect.width, rect.height, rect.getColor());
}

void View::Window::drawLine(const sf::Vector2f & p1, const sf::Vector2f & p2, const sf::Color & color)
{
    const float dist = std::sqrt((p1 - p2).x * (p1 - p2).x + (p1 - p2).y * (p1 - p2).y);

    sf::RectangleShape rect({dist, 1.0f});
    rect.setFillColor(color);
    rect.setPosition(p1);
    rect.rotate(static_cast<float>(180.0f * std::atan2((p2 - p1).y, (p2 - p1).x) / M_PI));
    draw(rect);
}

float View::Window::getFrameRate() const
{
    return m_frameRate;
}
