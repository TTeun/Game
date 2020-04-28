//
// Created by pc on 4/26/20.
//

#ifndef SFML_INTERSECTOR_H
#define SFML_INTERSECTOR_H

#include "../Entities/Shape/rectangle.h"
#include "intersectioninfo.h"

#include <SFML/Graphics/ConvexShape.hpp>

namespace Physics {

    class IntersectableObject;

    class Object;

    IntersectionInfo
    intersect(const Rectangle & movingRect, const sf::Vector2f & velocity, const Rectangle & staticRect, float dt);

    IntersectionInfo intersect(const IntersectableObject & movingObject, const Object & staticObject, float dt);

} // namespace Physics

#endif // SFML_INTERSECTOR_H
