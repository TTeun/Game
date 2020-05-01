//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_WINDOW_H
#define TEUN_GAME_WINDOW_H

#include "../Model/Entities/entitycontroller.h"
#include "../Model/Geometry/quadrilateral.h"
#include "../Model/Geometry/rectangle.h"
#include "../Model/Geometry/triangle.h"
#include "drawinterface.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace View {
    class Window : public sf::RenderWindow {

    public:
        Window(uint width, uint height, const char * title, bool showFrameRate = false);

        void setShowFrameRate(bool showFrameRate);

        float getDtInSeconds() const;

        sf::View calculateViewPort(const Model::Entities::Player & player);

        const Model::Geometry::Rectangle & getViewRect() const;

        void drawRectangle(float x, float y, float width, float height, const sf::Color & color = sf::Color::White);

        void drawRectangle(const Model::Geometry::ColoredRectangle & rect);

        void drawLine(const sf::Vector2f & p1, const sf::Vector2f & p2, const sf::Color & color = sf::Color::White);

        float getFrameRate() const;

        void drawModel(const Model::Entities::EntityController & entityController, DrawInterface & drawInterface);

        void drawTriangle(const Model::Geometry::Triangle & triangle, const sf::Color & color);

        void drawQuadrilateral(const Model::Geometry::Quadrilateral & quadrilateral, const sf::Color & color);

        void drawRectangle(const Model::Geometry::Rectangle & rect, const sf::Color & color = sf::Color::Black);

    private:
        bool m_showFrameRate;
        sf::Font m_font;
        sf::Text m_text;
        sf::Clock m_clock;

        float m_frameRate;

        float m_dt = 0.1;

        Model::Geometry::Rectangle m_viewRect;
        sf::Vector2f m_viewPortPositionVelocityOffset = {0.0f, 0.0f};
    };
} // namespace View

#endif // TEUN_GAME_WINDOW_H
