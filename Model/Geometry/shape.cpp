//
// Created by pc on 5/1/20.
//

#include "shape.h"

bool Model::Geometry::Shape::intersects(const Model::Geometry::Line & line) const
{
    for (const auto & it : m_rectangles) {
        if (it.intersects(line)) {
            return true;
        }
    }
    return false;
}

bool Model::Geometry::Shape::intersects(const Model::Geometry::Rectangle & rectangle) const
{
    for (const auto & it : m_rectangles) {
        if (it.intersects(rectangle)) {
            return true;
        }
    }
    return false;
}

Model::Geometry::Shape::Shape(const Model::Geometry::Rectangle && rectangle) : m_rectangles()
{
    m_rectangles.emplace_back(rectangle);
}
