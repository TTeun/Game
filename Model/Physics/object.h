//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_OBJECT_H
#define TEUN_GAME_OBJECT_H

#include "../Shapes/coloredrectangle.h"

#include <utility>

namespace Model {

    namespace Physics {

        class Object {

        public:
            const Shapes::ColoredRectangle & getShape() const;

        protected:
            Object(Shapes::ColoredRectangle &&shape);

            Model::Shapes::ColoredRectangle m_shape;
        };
    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_OBJECT_H
