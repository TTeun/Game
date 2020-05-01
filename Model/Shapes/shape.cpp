//
// Created by pc on 5/1/20.
//

#include "shape.h"

bool Model::Shapes::Shape::intersects(const Model::Shapes::Line &line) const {
    for (const auto &it : m_rectangles) {
        if (it.intersects(line)) {
            return true;
        }
    }
    return false;
}

bool Model::Shapes::Shape::intersects(const Model::Shapes::Rectangle &rectangle) const {
    for (const auto &it : m_rectangles) {
        if (it.intersects(rectangle)) {
            return true;
        }
    }
    return false;
}

Model::Shapes::Shape::Shape(const Model::Shapes::Rectangle &&rectangle) : m_rectangles() {
    m_rectangles.emplace_back(rectangle);
}

