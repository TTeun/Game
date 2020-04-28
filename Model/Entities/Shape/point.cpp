#include "point.h"

#include "../../../Aux/mathtools.h"

#include <cmath>

Point::Point(float x, float y) : Vector2(x, y)
{
}

Point::Point(const sf::Vector2f & point) : sf::Vector2f(point)
{
}

float Point::length() const
{
    return std::sqrt(MathTools::square(x) + MathTools::square(y));
}

void Point::normalize()
{
    float l = length();
    x /= l;
    y /= l;
}
