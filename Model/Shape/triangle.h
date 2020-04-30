//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_TRIANGLE_H
#define TEUN_GAME_TRIANGLE_H

#include "point.h"

namespace Model {

    namespace Shape {

        class Triangle {

        public:

            Model::Shape::Point getPoint(size_t i) const;

            Triangle(const Point &point1, const Point &point2, const Point &point3);

        private:
            Model::Shape::Point m_point0;
            Model::Shape::Point m_point1;
            Model::Shape::Point m_point2;

        };

    }
}

#endif //TEUN_GAME_TRIANGLE_H
