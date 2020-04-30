#include "point.h"

#include "../../Aux/mathtools.h"

#include <cmath>

Model::Shape::Point::Point(float x, float y) : Vector2(x, y) {
}

Model::Shape::Point::Point(const sf::Vector2f &point) : sf::Vector2f(point) {
}

float Model::Shape::Point::length() const {
    return std::sqrt(Aux::square(x) + Aux::square(y));
}

void Model::Shape::Point::normalize() {
    float l = length();
    x /= l;
    y /= l;
}

