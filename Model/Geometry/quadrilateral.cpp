//
// Created by pc on 4/30/20.
//

#include "quadrilateral.h"

#include <cassert>

namespace Model {

    namespace Geometry {
        Quadrilateral::Quadrilateral(const Model::Geometry::Point & point1,
                                     const Model::Geometry::Point & point2,
                                     const Model::Geometry::Point & point3,
                                     const Model::Geometry::Point & point4)
            : m_point0(point1), m_point1(point2), m_point2(point3), m_point3(point4)
        {
        }

        Model::Geometry::Point Model::Geometry::Quadrilateral::getPoint(size_t i) const
        {
            assert(i < 4);

            return (i == 0 ? m_point0 : (i == 1 ? m_point1 : (i == 2 ? m_point2 : m_point3)));
        }

    } // namespace Geometry
} // namespace Model
