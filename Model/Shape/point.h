//
// Created by pc on 4/28/20.
//

#ifndef TEUN_GAME_POINT_H
#define TEUN_GAME_POINT_H

#include <SFML/System.hpp>
#include <ostream>

namespace Model {
    namespace Shape {

        class Point : public sf::Vector2f {
        public:
            Point(float x, float y);

            Point(const sf::Vector2f &point);

            float length() const;

            void normalize();
        };
    } // namespace Shape
} // namespace Model
#endif // TEUN_GAME_POINT_H
