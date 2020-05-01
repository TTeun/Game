//
// Created by pc on 5/1/20.
//

#ifndef TEUN_GAME_SNAKE_H
#define TEUN_GAME_SNAKE_H

#include "coloredrectangle.h"

#include <memory>
#include <vector>

namespace Model {
    namespace Geometry {

        class Snake : public ColoredRectangle {

        public:
            Snake(const sf::FloatRect & rectangle, const sf::Color & color);

        private:
            std::vector<std::unique_ptr<Model::Geometry::ColoredRectangle>> m_followRectangles;
        };

    } // namespace Geometry

} // namespace Model

#endif // TEUN_GAME_SNAKE_H
