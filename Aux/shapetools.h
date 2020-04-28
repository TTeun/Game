//
// Created by pc on 4/27/20.
//

#ifndef SFML_SHAPETOOLS_H
#define SFML_SHAPETOOLS_H

#include "../Model/Entities/Shape/rectangle.h"

namespace sf {
    class RectangleShape;
    class ConvexShape;
} // namespace sf

class ShapeTools {

public:
    static Rectangle getBoundingRectangle(const sf::RectangleShape & rect);

    static Rectangle getBoundingRectangle(const Rectangle & rect);

    static Rectangle getBoundingRectangle(const sf::ConvexShape & rect);
};

#endif // SFML_SHAPETOOLS_H
