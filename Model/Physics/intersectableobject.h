//
// Created by pc on 4/26/20.
//

#ifndef SFML_INTERSECTABLEOBJECT_H
#define SFML_INTERSECTABLEOBJECT_H

#include "../../Aux/constpointerwrapper.h"
#include "physicsobject.h"

#include <cmath>
namespace Model {
    namespace Entities {
        class Level;
        class TerrainBlock;
    } // namespace Entities

    namespace Physics {

        class IntersectableObject : public PhysicsObject {

        public:
            explicit IntersectableObject(Model::Shape::Rectangle && shape);

            void update(float dt, const Model::Entities::Level & level, const Physics::Constants & constants);

        protected:
            void updateSnapped(float dt, const Model::Entities::Level & level, const Physics::Constants & constants);

            void updateUnSnapped(float dt, const Model::Entities::Level & level, const Physics::Constants & constants);

            void
            updateSnappedVertical(float dt, const Model::Entities::Level & level, const Physics::Constants & constants);

            virtual void updateSnappedHorizontal(float dt,
                                                 const Model::Entities::Level & level,
                                                 const Physics::Constants & constants);

            bool m_isGrounded = false;

            ConstPointerWrapper<Model::Entities::TerrainBlock> m_snappedTerrainBlock =
                ConstPointerWrapper<Model::Entities::TerrainBlock>(nullptr);

            enum WhereIsSnappedTerrain { BELOW, RIGHT, LEFT, ABOVE };

            WhereIsSnappedTerrain m_whereIsSnappedTerrain;

            WhereIsSnappedTerrain findWhereIsSnappedTerrain() const;
        };

    } // namespace Physics
} // namespace Model
#endif // SFML_INTERSECTABLEOBJECT_H
