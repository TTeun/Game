//
// Created by pc on 4/28/20.
//

#include "rectangle.h"

#include "../Entities/levelwrapper.h"

#include <cassert>

Model::Shape::Rectangle::Rectangle(const Point &size, const Point &position, const sf::Color &color) : m_color(color) {
    width = size.x;
    height = size.y;
    setPosition(position);
}

Model::Shape::Rectangle::Rectangle(const sf::FloatRect &rectangle, const sf::Color &color)
        : Rect(rectangle), m_color(color) {
}

sf::Vector2f Model::Shape::Rectangle::topLeft() const {
    return sf::Vector2f({left, top});
}

sf::Vector2f Model::Shape::Rectangle::topRight() const {
    return sf::Vector2f({left + width, top});
}

sf::Vector2f Model::Shape::Rectangle::bottomLeft() const {
    return sf::Vector2f({left, top + height});
}

sf::Vector2f Model::Shape::Rectangle::bottomRight() const {
    return sf::Vector2f({left + width, top + height});
}

bool Model::Shape::Rectangle::intersects(const Line &line) const {
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

Model::Shape::Rectangle Model::Shape::Rectangle::shrink(float factor) const {
    assert(factor <= 1.0f);
    sf::Vector2f dPosition = 0.5f * (1.0f - factor) * sf::Vector2f{this->width, this->height};
    sf::FloatRect rect{dPosition + sf::Vector2f{left, top}, factor * sf::Vector2f{width, height}};
    return Rectangle{rect};
}

float Model::Shape::Rectangle::getDistance(const Rectangle &other) const {
    return Line(getCenter(), other.getCenter()).length();
}

sf::Vector2f Model::Shape::Rectangle::getCenter() const {
    return {left + 0.5f * width, top + 0.5f * height};
}

void Model::Shape::Rectangle::setPosition(sf::Vector2f newPosition) {
    left = newPosition.x;
    top = newPosition.y;
}

void Model::Shape::Rectangle::move(const Point &point) {
    setPosition(getPosition() + point);
}

void Model::Shape::Rectangle::setColor(const sf::Color &color) {
    m_color = color;
}

const sf::Color &Model::Shape::Rectangle::getColor() const {
    return m_color;
}

bool Model::Shape::Rectangle::intersects(const Rectangle &other) const {
    return sf::FloatRect::intersects(other);
}

bool Model::Shape::Rectangle::intersects(const sf::FloatRect &other) const {
    return sf::FloatRect::intersects(other);
}

Model::Shape::Point Model::Shape::Rectangle::getPosition() const {
    return topLeft();
}

Model::Shape::Point Model::Shape::Rectangle::getSize() const {
    return {{width, height}};
}

bool Model::Shape::Rectangle::isMutuallyFullyVisible(const Rectangle &other,
                                                     const Entities::LevelWrapper &levelWrapper) const {
    return not(levelWrapper.intersects(Line{topRight(), other.topRight()}) ||
               levelWrapper.intersects(Line{topLeft(), other.topLeft()}) ||
               levelWrapper.intersects(Line{bottomRight(), other.bottomRight()}) ||
               levelWrapper.intersects(Line{bottomLeft(), other.bottomLeft()}));
}

Model::Shape::Rectangle operator+(const Model::Shape::Rectangle &rectangle, const Model::Shape::Point &point) {
    return Model::Shape::Rectangle(rectangle.getSize(), rectangle.getPosition() + point);
}
