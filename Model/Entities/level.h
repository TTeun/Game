//
// Created by pc on 4/26/20.
//

#ifndef SFML_LEVEL_H
#define SFML_LEVEL_H

#include "rectgraph.h"
#include "terrainblock.h"

#include <list>
#include <memory>

class TiXmlElement;

namespace Model {
    class Loaders;
}

namespace View {
    class Window;
}

namespace Entities {
    class Player;

    class Level {

        friend class Model::Loaders;

    public:
        Level();

        const std::list<std::unique_ptr<TerrainBlock>> & getTerrainBlocks() const;

        RectGraph getCornerRectGraph(float width, float height) const;

        RectGraph getCornerRectGraphWithPlayer(float width, float height, const Player & player) const;

        bool interSects(const Line & line) const;
        bool interSects(const sf::FloatRect & rect) const;

    private:
        std::list<std::unique_ptr<TerrainBlock>> m_terrainBlocks;

        size_t addTerrainBlock(float x, float y, float width, float height);
    };
} // namespace Entities

#endif // SFML_LEVEL_H
