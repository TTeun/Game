//
// Created by pc on 5/1/20.
//

#include "snake.h"

Model::Geometry::Snake::Snake(const sf::FloatRect & rectangle, const sf::Color & color)
    : ColoredRectangle(rectangle, color)
{
    for (size_t i = 0; i != 10; ++i) {
        m_followRectangles.emplace_back(new ColoredRectangle(*this, getColor()));
    }
}
