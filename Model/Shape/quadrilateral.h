//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_QUADRILATERAL_H
#define TEUN_GAME_QUADRILATERAL_H

#include "point.h"

namespace Model {

    namespace Shape {

        class Quadrilateral {

        private:
            Model::Shape::Point m_point0;
            Model::Shape::Point m_point1;
            Model::Shape::Point m_point2;
            Model::Shape::Point m_point3;

        public:
            Model::Shape::Point getPoint(size_t i) const;

            Quadrilateral(const Model::Shape::Point &point1, const Model::Shape::Point &point2,
                          const Model::Shape::Point &point3, const Model::Shape::Point &point4);


        };

    }
}

#endif //TEUN_GAME_QUADRILATERAL_H
