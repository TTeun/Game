//
// Created by pc on 4/26/20.
//

#ifndef SFML_LEVEL_H
#define SFML_LEVEL_H

#include "../DataStructures/rectgraph.h"
#include "terrainblock.h"

#include <list>
#include <memory>

class TiXmlElement;

namespace View {
    class Window;
}

namespace Model {

    namespace Entities {
        class Player;

        class Level {

        public:
            Level();

            const std::list<std::unique_ptr<TerrainBlock>> & getTerrainBlocks() const;

            DataStructures::RectGraph
            buildCornerRectGraphWithPlayer(float width, float height, const Player & player) const;

            bool intersects(const Shape::Line & line) const;

            bool intersects(const Shape::Rectangle & rect) const;

            size_t addTerrainBlock(float x, float y, float width, float height);

        private:
            DataStructures::RectGraph getCornerRectGraph(float width, float height) const;

            std::list<std::unique_ptr<Entities::TerrainBlock>> m_terrainBlocks;
        };
    } // namespace Entities
} // namespace Model

#endif // SFML_LEVEL_H
