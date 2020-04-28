//
// Created by pc on 4/26/20.
//

#ifndef SFML_INTERSECTABLEOBJECT_H
#define SFML_INTERSECTABLEOBJECT_H

#include "../Entities/terrainblock.h"
#include "physicsobject.h"

#include <cmath>

namespace Entities {
    class Level;
}

namespace Physics {

    class IntersectableObject : public PhysicsObject {

    public:
        IntersectableObject(Rectangle && shape, const sf::Vector2f & velocity);

        explicit IntersectableObject(Rectangle && shape);

        void update(float dt, const Entities::Level & level, const Physics::Constants & constants);

    protected:
        void updateSnapped(float dt, const Entities::Level & level, const Physics::Constants & constants);

        void updateUnSnapped(float dt, const Entities::Level & level, const Physics::Constants & constants);

        void updateSnappedBelow(float dt, const Entities::Level & level, const Physics::Constants & constants);

        virtual void
        updateSnappedHorizontal(float dt, const Entities::Level & level, const Physics::Constants & constants);

        bool m_isGrounded = false;

        const TerrainBlock * m_snappedTerrainBlock = nullptr;

        enum WhereIsSnappedTerrain {
            BELOW,
            RIGHT,
            LEFT,
            ABOVE // unused
        };

        WhereIsSnappedTerrain m_whereIsSnappedTerrain;

        void setWhereIsSnappedTerrain();
    };

} // namespace Physics

#endif // SFML_INTERSECTABLEOBJECT_H
