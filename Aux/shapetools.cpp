//
// Created by pc on 4/27/20.
//

#include "shapetools.h"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Rectangle ShapeTools::getBoundingRectangle(const sf::RectangleShape & rect)
{
    return Rectangle{rect.getSize(), rect.getPosition()};
}

Rectangle ShapeTools::getBoundingRectangle(const sf::ConvexShape & rect)
{
    const auto bounds = rect.getGlobalBounds();
    return Rectangle(bounds);
}

Rectangle ShapeTools::getBoundingRectangle(const Rectangle & rect)
{
    return rect;
}
