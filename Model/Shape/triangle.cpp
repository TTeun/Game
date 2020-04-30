//
// Created by pc on 4/30/20.
//

#include <cassert>
#include "triangle.h"

Model::Shape::Triangle::Triangle(const Model::Shape::Point &point1, const Model::Shape::Point &point2,
                                 const Model::Shape::Point &point3) : m_point0(point1), m_point1(point2),
                                                                      m_point2(point3) {}

Model::Shape::Point Model::Shape::Triangle::getPoint(size_t i) const {
    assert(i < 3);

    return i == 0 ? m_point0 : i == 1 ? m_point1 : m_point2;
}
