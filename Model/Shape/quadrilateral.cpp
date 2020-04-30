//
// Created by pc on 4/30/20.
//

#include <cassert>
#include "quadrilateral.h"

namespace Model {

    namespace Shape {
        Quadrilateral::Quadrilateral(const Model::Shape::Point &point1, const Model::Shape::Point &point2,
                                     const Model::Shape::Point &point3, const Model::Shape::Point &point4) :
                m_point0(point1), m_point1(point2), m_point2(point3), m_point3(point4) {}

        Model::Shape::Point Model::Shape::Quadrilateral::getPoint(size_t i) const {
            assert(i < 4);

            return (i == 0 ? m_point0 : (i == 1 ? m_point1 : (i == 2 ? m_point2 : m_point3)));
        }

    }
}
