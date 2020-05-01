#include "point.h"

#include "../../Aux/mathtools.h"

#include <cmath>

Model::Shapes::Point::Point(float x, float y) : Vector2(x, y) {
}

Model::Shapes::Point::Point(const sf::Vector2f &point) : sf::Vector2f(point) {
}

float Model::Shapes::Point::length() const {
    return std::sqrt(Aux::square(x) + Aux::square(y));
}

void Model::Shapes::Point::normalize() {
    float l = length();
    x /= l;
    y /= l;
}

