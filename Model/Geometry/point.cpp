#include "point.h"

#include "../../Aux/mathtools.h"

#include <cmath>

Model::Geometry::Point::Point(float x, float y) : Vector2(x, y)
{
}

Model::Geometry::Point::Point(const sf::Vector2f & point) : sf::Vector2f(point)
{
}

float Model::Geometry::Point::length() const
{
    return std::sqrt(Aux::square(x) + Aux::square(y));
}

void Model::Geometry::Point::normalize()
{
    float l = length();
    x /= l;
    y /= l;
}
