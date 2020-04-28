//
// Created by pc on 4/28/20.
//

#include "rectangle.h"

#include <cassert>

Rectangle::Rectangle(const Point & size, const Point & position, const sf::Color & color) : m_color(color)
{
    width  = size.x;
    height = size.y;
    setPosition(position);
}

Rectangle::Rectangle(const sf::FloatRect & rectangle, const sf::Color & color) : Rect(rectangle), m_color(color)
{
}

sf::Vector2f Rectangle::topLeft() const
{
    return sf::Vector2f({left, top});
}
sf::Vector2f Rectangle::topRight() const
{
    return sf::Vector2f({left + width, top});
}

sf::Vector2f Rectangle::bottomLeft() const
{
    return sf::Vector2f({left, top + height});
}

sf::Vector2f Rectangle::bottomRight() const
{
    return sf::Vector2f({left + width, top + height});
}

bool Rectangle::intersects(const Line & line) const
{
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

Rectangle Rectangle::shrink(float factor) const
{
    assert(factor <= 1.0f);
    sf::Vector2f dPosition = 0.5f * (1.0f - factor) * sf::Vector2f{this->width, this->height};
    sf::FloatRect rect{dPosition + sf::Vector2f{left, top}, factor * sf::Vector2f{width, height}};
    return Rectangle{rect};
}

float Rectangle::getDistance(const Rectangle & other) const
{
    return Line(getCenter(), other.getCenter()).length();
}

sf::Vector2f Rectangle::getCenter() const
{
    return {left + 0.5f * width, top + 0.5f * height};
}

void Rectangle::setPosition(sf::Vector2f newPosition)
{
    left = newPosition.x;
    top  = newPosition.y;
}

void Rectangle::move(const Point & point)
{
    setPosition(getPosition() + point);
}

void Rectangle::setColor(const sf::Color & color)
{
    m_color = color;
}

const sf::Color & Rectangle::getColor() const
{
    return m_color;
}

bool Rectangle::intersects(const Rectangle & other) const
{
    return sf::FloatRect::intersects(other);
}

bool Rectangle::intersects(const sf::FloatRect & other) const
{
    return sf::FloatRect::intersects(other);
}
Point Rectangle::getPosition() const
{
    return topLeft();
}
Point Rectangle::getSize() const
{
    return {{width, height}};
}

Rectangle operator+(const Rectangle & rectangle, const Point & point)
{
    return Rectangle(rectangle.getSize(), rectangle.getPosition() + point);
}
