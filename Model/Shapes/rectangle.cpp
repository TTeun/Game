//
// Created by pc on 4/28/20.
//

#include "rectangle.h"

#include "../Entities/levelwrapper.h"

#include <cassert>

Model::Shapes::Rectangle::Rectangle(const Point &size, const Point &position) {
    width = size.x;
    height = size.y;
    setPosition(position);
}

Model::Shapes::Rectangle::Rectangle(const sf::FloatRect &rectangle)
        : Rect(rectangle) {
}

sf::Vector2f Model::Shapes::Rectangle::topLeft() const {
    return sf::Vector2f({left, top});
}

sf::Vector2f Model::Shapes::Rectangle::topRight() const {
    return sf::Vector2f({left + width, top});
}

sf::Vector2f Model::Shapes::Rectangle::bottomLeft() const {
    return sf::Vector2f({left, top + height});
}

sf::Vector2f Model::Shapes::Rectangle::bottomRight() const {
    return sf::Vector2f({left + width, top + height});
}

bool Model::Shapes::Rectangle::intersects(const Line &line) const {
    if (line.intersects({topLeft(), topRight()})) {
        return true;
    } else if (line.intersects({topLeft(), bottomLeft()})) {
        return true;
    } else if (line.intersects({topRight(), bottomRight()})) {
        return true;
    } else if (line.intersects({bottomLeft(), bottomLeft()})) {
        return true;
    }
    return false;
}

Model::Shapes::Rectangle Model::Shapes::Rectangle::shrink(float factor) const {
    assert(factor <= 1.0f);
    sf::Vector2f dPosition = 0.5f * (1.0f - factor) * sf::Vector2f{this->width, this->height};
    sf::FloatRect rect{dPosition + sf::Vector2f{left, top}, factor * sf::Vector2f{width, height}};
    return Rectangle{rect};
}

float Model::Shapes::Rectangle::getDistance(const Rectangle &other) const {
    return Line(getCenter(), other.getCenter()).length();
}

sf::Vector2f Model::Shapes::Rectangle::getCenter() const {
    return {left + 0.5f * width, top + 0.5f * height};
}

void Model::Shapes::Rectangle::setPosition(sf::Vector2f newPosition) {
    left = newPosition.x;
    top = newPosition.y;
}

void Model::Shapes::Rectangle::move(const Point &point) {
    setPosition(getPosition() + point);
}

bool Model::Shapes::Rectangle::intersects(const Rectangle &other) const {
    return sf::FloatRect::intersects(other);
}

bool Model::Shapes::Rectangle::intersects(const sf::FloatRect &other) const {
    return sf::FloatRect::intersects(other);
}

Model::Shapes::Point Model::Shapes::Rectangle::getPosition() const {
    return topLeft();
}

Model::Shapes::Point Model::Shapes::Rectangle::getSize() const {
    return {{width, height}};
}

bool Model::Shapes::Rectangle::isMutuallyFullyVisible(const Rectangle &other,
                                                      const Entities::LevelWrapper &levelWrapper) const {
    return not(levelWrapper.intersects(Line{topRight(), other.topRight()}) ||
               levelWrapper.intersects(Line{topLeft(), other.topLeft()}) ||
               levelWrapper.intersects(Line{bottomRight(), other.bottomRight()}) ||
               levelWrapper.intersects(Line{bottomLeft(), other.bottomLeft()}));
}

Model::Shapes::Rectangle operator+(const Model::Shapes::Rectangle &rectangle, const Model::Shapes::Point &point) {
    return Model::Shapes::Rectangle(rectangle.getSize(), rectangle.getPosition() + point);
}
