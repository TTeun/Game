#include "point.h"

#include "../../Aux/mathtools.h"

#include <cassert>
#include <cmath>

Model::Geometry::Point::Point(float x, float y) : Vector2(x, y)
{
}

Model::Geometry::Point::Point(const sf::Vector2f & point) : sf::Vector2f(point)
{
}

float Model::Geometry::Point::getLength() const
{
    return std::sqrt(Aux::square(x) + Aux::square(y));
}

void Model::Geometry::Point::normalize()
{
    float length = getLength();
    x /= length;
    y /= length;
}

void Model::Geometry::Point::setSize(float newLength)
{
    assert(newLength != 0.0f);
    const float length = this->getLength();
    x *= newLength / length;
    y *= newLength / length;
}

void Model::Geometry::Point::clampLength(float maxlength)
{
    if (getLength() > maxlength) {
        setSize(maxlength);
    }
}
