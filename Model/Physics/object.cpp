//
// Created by pc on 4/28/20.
//

#include "object.h"

const Model::Shape::Rectangle &Model::Physics::Object::getShape() const {
    return m_shape;
}

Model::Physics::Object::Object(Model::Shape::Rectangle &&shape) : m_shape(std::move(shape)) {
}
