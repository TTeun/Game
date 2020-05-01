//
// Created by pc on 4/28/20.
//

#ifndef TEUN_GAME_LINE_H
#define TEUN_GAME_LINE_H

#include "point.h"

#include <SFML/System/Vector2.hpp>

namespace Model {
    namespace Geometry {

        class Line {

        public:
            Line(const Point & p1, const Point & p2);

            bool intersects(const Line & otherLine) const;

            float length() const;

        private:
            Point m_point1;
            Point m_point2;
        };
    } // namespace Geometry
} // namespace Model
#endif // TEUN_GAME_LINE_H
