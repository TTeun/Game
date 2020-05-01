//
// Created by pc on 4/28/20.
//

#include "object.h"

const Model::Geometry::ColoredRectangle & Model::Physics::Object::getShape() const
{
    return m_shape;
}

Model::Physics::Object::Object(Geometry::ColoredRectangle && shape) : m_shape(std::move(shape))
{
}
