//
// Created by pc on 4/28/20.
// topLeft

#ifndef TEUN_GAME_RECTANGLE_H
#define TEUN_GAME_RECTANGLE_H

#include "line.h"

#include <SFML/Graphics/Rect.hpp>

namespace Model {
    namespace Entities {
        class LevelWrapper;
    } // namespace Entities
} // namespace Model

namespace Model {

    namespace Shapes {

        class Rectangle : public sf::FloatRect {

        public:
            explicit Rectangle(const sf::FloatRect &rectangle);

            Rectangle(const Point &size, const Point &position);

            sf::Vector2f topLeft() const;

            sf::Vector2f topRight() const;

            sf::Vector2f bottomLeft() const;

            sf::Vector2f bottomRight() const;

            float getDistance(const Rectangle &other) const;

            sf::Vector2f getCenter() const;

            bool intersects(const Line &line) const;

            bool intersects(const Rectangle &other) const;

            bool intersects(const sf::FloatRect &other) const;

            Rectangle shrink(float factor) const;

            void setPosition(sf::Vector2f newPosition);

            void move(const Point &offset);

            Point getPosition() const;

            Point getSize() const;

            bool
            isMutuallyFullyVisible(const Rectangle &other, const Model::Entities::LevelWrapper &levelWrapper) const;
        };
    } // namespace Shapes
} // namespace Model
Model::Shapes::Rectangle operator+(const Model::Shapes::Rectangle &rectangle, const Model::Shapes::Point &point);

#endif // TEUN_GAME_RECTANGLE_H
