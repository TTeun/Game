//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_QUADRILATERAL_H
#define TEUN_GAME_QUADRILATERAL_H

#include "point.h"

namespace Model {

    namespace Shapes {

        class Quadrilateral {

        private:
            Model::Shapes::Point m_point0;
            Model::Shapes::Point m_point1;
            Model::Shapes::Point m_point2;
            Model::Shapes::Point m_point3;

        public:
            Model::Shapes::Point getPoint(size_t i) const;

            Quadrilateral(const Model::Shapes::Point &point1, const Model::Shapes::Point &point2,
                          const Model::Shapes::Point &point3, const Model::Shapes::Point &point4);


        };

    }
}

#endif //TEUN_GAME_QUADRILATERAL_H
