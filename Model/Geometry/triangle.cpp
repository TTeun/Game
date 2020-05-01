//
// Created by pc on 4/30/20.
//

#include "triangle.h"

#include <cassert>

Model::Geometry::Triangle::Triangle(const Model::Geometry::Point & point1,
                                    const Model::Geometry::Point & point2,
                                    const Model::Geometry::Point & point3)
    : m_point0(point1), m_point1(point2), m_point2(point3)
{
}

Model::Geometry::Point Model::Geometry::Triangle::getPoint(size_t i) const
{
    assert(i < 3);

    return i == 0 ? m_point0 : i == 1 ? m_point1 : m_point2;
}
