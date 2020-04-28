//
// Created by pc on 4/26/20.
//

#ifndef SFML_OBJECT_H
#define SFML_OBJECT_H

#include <utility>

namespace Physics {

    template <class T>
    class Object {

    public:
        const T & getShape() const
        {
            return m_shape;
        }

    protected:
        Object(T && shape) : m_shape(std::move(shape))
        {
        }

        T m_shape;
    };
} // namespace Physics

#endif // SFML_OBJECT_H
