//
// Created by pc on 4/28/20.
//

#include "line.h"

#include <cmath>

bool intersection(sf::Vector2f start1, sf::Vector2f end1, sf::Vector2f start2, sf::Vector2f end2)
{
    float ax = end1.x - start1.x; // direction of line a
    float ay = end1.y - start1.y; // ax and ay as above

    float bx = start2.x - end2.x; // direction of line b, reversed
    float by = start2.y - end2.y; // really -by and -by as above

    float dx = start2.x - start1.x; // right-hand side
    float dy = start2.y - start1.y;

    float det = ax * by - ay * bx;

    if (det <= 0.001f)
        return false;

    float r = (dx * by - dy * bx) / det;
    float s = (ax * dy - ay * dx) / det;

    return !(r < 0 || r > 1 || s < 0 || s > 1);
}

bool Line::intersects(const Line & otherLine) const
{
    return intersection({m_point1.x, m_point1.y},
                        {m_point2.x, m_point2.y},
                        {otherLine.m_point1.x, otherLine.m_point1.y},
                        {otherLine.m_point2.x, otherLine.m_point2.y});
}

Line::Line(const sf::Vector2f & p1, const sf::Vector2f & p2) : m_point1(p1), m_point2(p2)
{
}

float Line::length() const
{
    return std::sqrt((m_point1.x - m_point2.x) * (m_point1.x - m_point2.x) +
                     (m_point1.y - m_point2.y) * (m_point1.y - m_point2.y));
}