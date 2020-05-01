//
// Created by pc on 5/1/20.
//

#ifndef TEUN_GAME_SHAPE_H
#define TEUN_GAME_SHAPE_H

#include <memory>
#include <vector>
#include "rectangle.h"
#include "line.h"

namespace Model {
    namespace Entities {
        class LevelWrapper;
    }
}

namespace Model {
    namespace Shapes {

        class Shape {

        public:

            Shape(const Model::Shapes::Rectangle &&rectangle);

            virtual bool intersects(const Line &line) const;

            virtual bool intersects(const Rectangle &rectangle) const;

        private:
            std::vector<Model::Shapes::Rectangle> m_rectangles;

        };
    }
}

#endif //TEUN_GAME_SHAPE_H
