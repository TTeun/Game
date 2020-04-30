//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_WINDOW_H
#define TEUN_GAME_WINDOW_H

#include "../Model/Shape/rectangle.h"
#include "drawinterface.h"
#include "../Model/Shape/triangle.h"
#include "../Model/Shape/quadrilateral.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace View {
    class Window : public sf::RenderWindow {

    public:
        Window(uint width, uint height, const char *title, bool showFrameRate = false);

        void setShowFrameRate(bool showFrameRate);

        float getDtInSeconds() const;

        sf::View calculateViewPort(const Model::Entities::Player &player);

        const sf::FloatRect &getViewRect() const;

        void drawRectangle(float x, float y, float width, float height, const sf::Color &color = sf::Color::White);

        void drawRectangle(const Model::Shape::Rectangle &rec);

        void drawLine(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Color &color = sf::Color::White);

        float getFrameRate() const;

        void drawModel(const Model::EntityController &entityController, DrawInterface &drawInterface);

        void drawTriangle(const Model::Shape::Triangle &triangle, const sf::Color &color);

        void drawQuadrilateral(const Model::Shape::Quadrilateral &quadrilateral, const sf::Color &color);

    private:
        bool m_showFrameRate;
        sf::Font m_font;
        sf::Text m_text;
        sf::Clock m_clock;

        float m_frameRate;

        float m_dt = 0.1;

        sf::FloatRect m_viewRect;
        sf::Vector2f m_viewPortPositionVelocityOffset = {0.0f, 0.0f};

    };
} // namespace View

#endif // TEUN_GAME_WINDOW_H
