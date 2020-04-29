//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_INTERSECTABLEOBJECT_H
#define TEUN_GAME_INTERSECTABLEOBJECT_H

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
            explicit IntersectableObject(Model::Shape::Rectangle &&shape);

            void update(float dt, const Model::Entities::Level &level, const Physics::Constants &constants);

        protected:
            void updateSnapped(float dt, const Model::Entities::Level &level, const Physics::Constants &constants);

            void updateUnSnapped(float dt, const Model::Entities::Level &level, const Physics::Constants &constants);

            void
            updateSnappedVertical(float dt, const Model::Entities::Level &level, const Physics::Constants &constants);

            virtual void updateSnappedHorizontal(float dt,
                                                 const Model::Entities::Level &level,
                                                 const Physics::Constants &constants);

            void checkAndHandlePressedIntoWall(float dt, const Physics::Constants &constants);

            bool m_isGrounded = false;

            void unSnap();

            Aux::ConstPointerWrapper<Model::Entities::TerrainBlock> m_snappedTerrainBlock =
                    Aux::ConstPointerWrapper<Model::Entities::TerrainBlock>(nullptr);

            enum WHERE_IS_SNAPPED_TERRAIN {
                BELOW, RIGHT, LEFT, ABOVE
            };

            WHERE_IS_SNAPPED_TERRAIN m_whereIsSnappedTerrain;

            WHERE_IS_SNAPPED_TERRAIN findWhereIsSnappedTerrain() const;
        };

    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_INTERSECTABLEOBJECT_H
