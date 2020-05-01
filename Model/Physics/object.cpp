//
// Created by pc on 4/28/20.
//

#include "object.h"

const Model::Shapes::ColoredRectangle & Model::Physics::Object::getShape() const {
    return m_shape;
}

Model::Physics::Object::Object(Shapes::ColoredRectangle &&shape) : m_shape(std::move(shape)) {
}
