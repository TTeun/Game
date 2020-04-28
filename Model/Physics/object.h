//
// Created by pc on 4/26/20.
//

#ifndef SFML_OBJECT_H
#define SFML_OBJECT_H

#include "../Entities/Shape/rectangle.h"

#include <utility>

namespace Physics {

    class Object {

    public:
        const Rectangle & getShape() const;

    protected:
        Object(Rectangle && shape);

        Rectangle m_shape;
    };
} // namespace Physics

#endif // SFML_OBJECT_H
