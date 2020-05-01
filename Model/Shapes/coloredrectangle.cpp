//
// Created by pc on 4/30/20.
//

#include "coloredrectangle.h"


Model::Shapes::ColoredRectangle::ColoredRectangle(const sf::FloatRect &rectangle, const sf::Color &color) : Rectangle(
        rectangle), m_color(color) {

}

Model::Shapes::ColoredRectangle::ColoredRectangle(const Model::Shapes::Point &size, const Model::Shapes::Point &position,
                                                  const sf::Color &color) : Rectangle(size, position), m_color(color) {
}

const sf::Color &Model::Shapes::ColoredRectangle::getColor() const {
    return m_color;
}

void Model::Shapes::ColoredRectangle::setColor(const sf::Color &color) {
    m_color = color;
}
