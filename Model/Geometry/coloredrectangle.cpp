//
// Created by pc on 4/30/20.
//

#include "coloredrectangle.h"

Model::Geometry::ColoredRectangle::ColoredRectangle(const sf::FloatRect & rectangle, const sf::Color & color)
    : Rectangle(rectangle), m_color(color)
{
}

Model::Geometry::ColoredRectangle::ColoredRectangle(const Model::Geometry::Point & size,
                                                    const Model::Geometry::Point & position,
                                                    const sf::Color & color)
    : Rectangle(size, position), m_color(color)
{
}

const sf::Color & Model::Geometry::ColoredRectangle::getColor() const
{
    return m_color;
}

void Model::Geometry::ColoredRectangle::setColor(const sf::Color & color)
{
    m_color = color;
}
