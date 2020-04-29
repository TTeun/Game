//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_LEVEL_H
#define TEUN_GAME_LEVEL_H

#include "terrainblock.h"
#include "../DataStructures/rectgraph.h"

#include <list>
#include <memory>

class TiXmlElement;

namespace View {
    class Window;
}

namespace Model {

    class Loaders;

    namespace Entities {
        class Player;

        class Level {

            friend LevelWrapper;
            friend Loaders;

        public:
            Level();

            const std::list<std::unique_ptr<TerrainBlock>> &getTerrainBlocks() const;

            DataStructures::RectGraph
            buildCornerRectGraphWithPlayer(float width, float height, const Player &player) const;

        private:

            bool intersects(const Shape::Line &line) const;

            bool intersects(const Shape::Rectangle &rect) const;

            size_t addTerrainBlock(float x, float y, float width, float height);

            DataStructures::RectGraph getCornerRectGraph(float width, float height) const;

            std::list<std::unique_ptr<Entities::TerrainBlock>> m_terrainBlocks;
        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_LEVEL_H
