//
// Created by pc on 4/30/20.
//

#include <cassert>
#include "triangle.h"

Model::Shapes::Triangle::Triangle(const Model::Shapes::Point &point1, const Model::Shapes::Point &point2,
                                  const Model::Shapes::Point &point3) : m_point0(point1), m_point1(point2),
                                                                        m_point2(point3) {}

Model::Shapes::Point Model::Shapes::Triangle::getPoint(size_t i) const {
    assert(i < 3);

    return i == 0 ? m_point0 : i == 1 ? m_point1 : m_point2;
}
