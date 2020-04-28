//
// Created by pc on 4/28/20.
// topLeft

#ifndef SFML_RECTANGLE_H
#define SFML_RECTANGLE_H

#include "line.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

class Rectangle : public sf::FloatRect {

public:
    explicit Rectangle(const sf::FloatRect & rectangle, const sf::Color & color = sf::Color::White);

    Rectangle(const Point & size, const Point & position, const sf::Color & color = sf::Color::White);

    sf::Vector2f topLeft() const;

    sf::Vector2f topRight() const;

    sf::Vector2f bottomLeft() const;

    sf::Vector2f bottomRight() const;

    float getDistance(const Rectangle & other) const;

    sf::Vector2f getCenter() const;

    bool intersects(const Line & line) const;

    Rectangle shrink(float factor) const;

    void setPosition(sf::Vector2f newPosition);

    void move(const Point & offset);

    const sf::Color & getColor() const;

    void setColor(const sf::Color & color);

    bool intersects(const Rectangle & other) const;

    bool intersects(const sf::FloatRect & other) const;

    Point getPosition() const
    {
        return topLeft();
    }

    Point getSize() const
    {
        return {{width, height}};
    }

private:
    //    sf::Color m_color;
};

#endif // SFML_RECTANGLE_H
