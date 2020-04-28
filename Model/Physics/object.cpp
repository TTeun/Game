//
// Created by pc on 4/28/20.
//

#include "object.h"

const Rectangle & Physics::Object::getShape() const
{
    return m_shape;
}
Physics::Object::Object(Rectangle && shape) : m_shape(std::move(shape))
{
}
