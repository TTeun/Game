//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_QUADRILATERAL_H
#define TEUN_GAME_QUADRILATERAL_H

#include "point.h"

namespace Model {

    namespace Geometry {

        class Quadrilateral {

        private:
            Model::Geometry::Point m_point0;
            Model::Geometry::Point m_point1;
            Model::Geometry::Point m_point2;
            Model::Geometry::Point m_point3;

        public:
            Model::Geometry::Point getPoint(size_t i) const;

            Quadrilateral(const Model::Geometry::Point & point1,
                          const Model::Geometry::Point & point2,
                          const Model::Geometry::Point & point3,
                          const Model::Geometry::Point & point4);
        };

    } // namespace Geometry
} // namespace Model

#endif // TEUN_GAME_QUADRILATERAL_H
