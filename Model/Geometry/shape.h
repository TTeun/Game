//
// Created by pc on 5/1/20.
//

#ifndef TEUN_GAME_SHAPE_H
#define TEUN_GAME_SHAPE_H

#include "line.h"
#include "rectangle.h"

#include <memory>
#include <vector>

namespace Model {
    namespace Entities {
        class LevelWrapper;
    }
} // namespace Model

namespace Model {
    namespace Geometry {

        class Shape {

        public:
            Shape(const Model::Geometry::Rectangle && rectangle);

            virtual bool intersects(const Line & line) const;

            virtual bool intersects(const Rectangle & rectangle) const;

        private:
            std::vector<Model::Geometry::Rectangle> m_rectangles;
        };
    } // namespace Geometry
} // namespace Model

#endif // TEUN_GAME_SHAPE_H
