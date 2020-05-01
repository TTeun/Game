//
// Created by pc on 4/28/20.
//

#include "rectangle.h"

#include "../Entities/levelwrapper.h"

#include <cassert>

Model::Geometry::Rectangle::Rectangle(const Point & size, const Point & position)
{
    width  = size.x;
    height = size.y;
    setPosition(position);
}

Model::Geometry::Rectangle::Rectangle(const sf::FloatRect & rectangle) : Rect(rectangle)
{
}

sf::Vector2f Model::Geometry::Rectangle::topLeft() const
{
    return sf::Vector2f({left, top});
}

sf::Vector2f Model::Geometry::Rectangle::topRight() const
{
    return sf::Vector2f({left + width, top});
}

sf::Vector2f Model::Geometry::Rectangle::bottomLeft() const
{
    return sf::Vector2f({left, top + height});
}

sf::Vector2f Model::Geometry::Rectangle::bottomRight() const
{
    return sf::Vector2f({left + width, top + height});
}

bool Model::Geometry::Rectangle::intersects(const Line & line) const
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

Model::Geometry::Rectangle Model::Geometry::Rectangle::shrink(float factor) const
{
    assert(factor <= 1.0f);
    sf::Vector2f dPosition = 0.5f * (1.0f - factor) * sf::Vector2f{this->width, this->height};
    sf::FloatRect rect{dPosition + sf::Vector2f{left, top}, factor * sf::Vector2f{width, height}};
    return Rectangle{rect};
}

float Model::Geometry::Rectangle::getDistance(const Rectangle & other) const
{
    return Line(getCenter(), other.getCenter()).length();
}

sf::Vector2f Model::Geometry::Rectangle::getCenter() const
{
    return {left + 0.5f * width, top + 0.5f * height};
}

void Model::Geometry::Rectangle::setPosition(sf::Vector2f newPosition)
{
    left = newPosition.x;
    top  = newPosition.y;
}

void Model::Geometry::Rectangle::move(const Point & point)
{
    setPosition(getPosition() + point);
}

bool Model::Geometry::Rectangle::intersects(const Rectangle & other) const
{
    return sf::FloatRect::intersects(other);
}

Model::Geometry::Point Model::Geometry::Rectangle::getPosition() const
{
    return topLeft();
}

Model::Geometry::Point Model::Geometry::Rectangle::getSize() const
{
    return {{width, height}};
}

bool Model::Geometry::Rectangle::isMutuallyFullyVisible(const Rectangle & other,
                                                        const Entities::LevelWrapper & levelWrapper) const
{
    return not(levelWrapper.intersects(Line{topRight(), other.topRight()}) ||
               levelWrapper.intersects(Line{topLeft(), other.topLeft()}) ||
               levelWrapper.intersects(Line{bottomRight(), other.bottomRight()}) ||
               levelWrapper.intersects(Line{bottomLeft(), other.bottomLeft()}));
}
Model::Geometry::Vector2d
Model::Geometry::Rectangle::getVectorToOtherRectangle(const Model::Geometry::Rectangle & other) const
{
    return other.getCenter() - getCenter();
}

Model::Geometry::Rectangle operator+(const Model::Geometry::Rectangle & rectangle, const Model::Geometry::Point & point)
{
    return Model::Geometry::Rectangle(rectangle.getSize(), rectangle.getPosition() + point);
}
