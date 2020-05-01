//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_TERRAINBLOCK_H
#define TEUN_GAME_TERRAINBLOCK_H

#include "../Physics/object.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace View {
    class Window;
}

namespace Model {

    namespace Entities {

        class TerrainBlock : public Physics::Object {
        public:
            TerrainBlock(const size_t id, float width, float height, const Geometry::Point & position);

            TerrainBlock(size_t id, Model::Geometry::ColoredRectangle && coloredRectangle);

            size_t getId() const;

        private:
            const size_t m_id;
        };
    } // namespace Entities
} // namespace Model
#endif // TEUN_GAME_TERRAINBLOCK_H
