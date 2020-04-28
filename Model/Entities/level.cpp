//
// Created by pc on 4/26/20.
//

#include "level.h"

#include "Shape/line.h"
#include "Shape/rectangle.h"
#include "player.h"

#include <algorithm>

Entities::Level::Level()
{
}

const std::list<std::unique_ptr<TerrainBlock>> & Entities::Level::getTerrainBlocks() const
{
    return m_terrainBlocks;
}

size_t Entities::Level::addTerrainBlock(float x, float y, float width, float height)
{
    const size_t id = m_terrainBlocks.size();
    m_terrainBlocks.emplace_back(new TerrainBlock(id, width, height, {x, y}));
    return id;
}

bool Entities::Level::interSects(const sf::FloatRect & rect) const
{
    for (const auto & terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().::sf::FloatRect::intersects(rect)) {
            return true;
        }
    }
    return false;
}

bool Entities::Level::interSects(const Line & line) const
{
    for (const auto & terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().intersects(line)) {
            return true;
        }
    }
    return false;
}

RectGraph Entities::Level::getCornerRectGraph(float width, float height) const
{
    return RectGraph(width, height, *this);
}

RectGraph
Entities::Level::getCornerRectGraphWithPlayer(float width, float height, const Entities::Player & player) const
{
    auto graph = getCornerRectGraph(width, height);
    graph.addTarget(player.getShape(), *this, 0.9f);
    return graph;
}
