//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_COLOREDRECTANGLE_H
#define TEUN_GAME_COLOREDRECTANGLE_H

#include "rectangle.h"

#include <SFML/Graphics/Color.hpp>

namespace Model {
    namespace Geometry {

        class ColoredRectangle : public Rectangle {

        public:
            explicit ColoredRectangle(const sf::FloatRect & rectangle, const sf::Color & color = sf::Color::Black);

            ColoredRectangle(const Point & size, const Point & position, const sf::Color & color = sf::Color::Black);

            const sf::Color & getColor() const;

            void setColor(const sf::Color & color);

        private:
            sf::Color m_color = sf::Color::Black;
        };
    } // namespace Geometry
} // namespace Model

#endif // TEUN_GAME_COLOREDRECTANGLE_H
