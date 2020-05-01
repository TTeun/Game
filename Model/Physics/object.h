//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_OBJECT_H
#define TEUN_GAME_OBJECT_H

#include "../Geometry/coloredrectangle.h"

#include <utility>

namespace Model {

    namespace Physics {

        class Object {

        public:
            const Geometry::ColoredRectangle & getShape() const;

        protected:
            Object(Geometry::ColoredRectangle && shape);

            Model::Geometry::ColoredRectangle m_shape;
        };
    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_OBJECT_H
