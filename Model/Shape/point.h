//
// Created by pc on 4/28/20.
//

#ifndef SFML_POINT_H
#define SFML_POINT_H

#include <SFML/System.hpp>

namespace Model {
    namespace Shape {

        class Point : public sf::Vector2f {
        public:
            Point(float x, float y);

            Point(const sf::Vector2f & point);

            float length() const;

            void normalize();
        };
    } // namespace Shape
} // namespace Model
#endif // SFML_POINT_H
