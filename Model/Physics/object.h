//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_OBJECT_H
#define TEUN_GAME_OBJECT_H

#include "../Shape/rectangle.h"

#include <utility>

namespace Model {

    namespace Physics {

        class Object {

        public:
            const Model::Shape::Rectangle &getShape() const;

        protected:
            Object(Model::Shape::Rectangle &&shape);

            Model::Shape::Rectangle m_shape;
        };
    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_OBJECT_H
