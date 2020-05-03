//
// Created by pc on 4/28/20.
//

#ifndef TEUN_GAME_POINT_H
#define TEUN_GAME_POINT_H

#include <SFML/System.hpp>

namespace Model {
    namespace Geometry {

        class Point : public sf::Vector2f {
        public:
            Point() = default;

            Point(float x, float y);

            Point(const sf::Vector2f & point);

            float getLength() const;

            void normalize();

            void setSize(float newLength);

            void clampLength(float maxlength);
        };

        typedef Point Vector2d;

    } // namespace Geometry
} // namespace Model

#include <ostream>

#endif // TEUN_GAME_POINT_H
