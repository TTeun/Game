//
// Created by pc on 4/26/20.
//

#include "shapeFactory.h"

#include "../../Aux/uniform.h"

#include <math.h>

sf::ConvexShape Entities::ShapeFactory::buildBlob(const Uniform & numberOfPointsUniform, const Uniform & sizeUniform)
{
    sf::ConvexShape shape(numberOfPointsUniform.get());
    for (size_t i = 0; i != shape.getPointCount(); ++i) {
        shape.setPoint(
            i,
            sf::Vector2f(static_cast<float>(sizeUniform.get() * sin(2.0 * M_PI * i / shape.getPointCount())),
                         static_cast<float>(sizeUniform.get() * cos(2.0 * M_PI * i / shape.getPointCount()))));
    }
    return shape;
}