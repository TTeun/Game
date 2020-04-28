//
// Created by pc on 4/26/20.
//

#ifndef SFML_INTERSECTABLEOBJECT_H
#define SFML_INTERSECTABLEOBJECT_H

#include "../../Aux/shapetools.h"
#include "../Entities/level.h"
#include "intersectioninfo.h"
#include "intersector.h"
#include "physicsobject.h"

#include <cmath>
#include <iostream>

namespace Physics {

    class IntersectableObject : public PhysicsObject {

    public:
        IntersectableObject(Rectangle && shape, const sf::Vector2f & velocity);

        explicit IntersectableObject(Rectangle && shape);

        void update(float dt, const Entities::Level & level, const Physics::Constants & constants);

    protected:
        bool m_isGrounded = false;
    };

} // namespace Physics

#endif // SFML_INTERSECTABLEOBJECT_H
