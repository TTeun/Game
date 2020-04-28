//
// Created by pc on 4/28/20.
//

#ifndef SFML_LINE_H
#define SFML_LINE_H

#include "point.h"

#include <SFML/System/Vector2.hpp>

namespace Model {
    namespace Shape {

        class Line {

        public:
            Line(const sf::Vector2f & p1, const sf::Vector2f & p2);

            bool intersects(const Line & otherLine) const;

            float length() const;

        private:
            Point m_point1;
            Point m_point2;
        };
    } // namespace Shape
} // namespace Model
#endif // SFML_LINE_H
