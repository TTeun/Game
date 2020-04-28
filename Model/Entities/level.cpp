//
// Created by pc on 4/26/20.
//

#include "level.h"

#include "player.h"

Model::Entities::Level::Level()
{
}

const std::list<std::unique_ptr<Model::Entities::TerrainBlock>> & Model::Entities::Level::getTerrainBlocks() const
{
    return m_terrainBlocks;
}

size_t Model::Entities::Level::addTerrainBlock(float x, float y, float width, float height)
{
    const size_t id = m_terrainBlocks.size();
    m_terrainBlocks.emplace_back(new TerrainBlock(id, width, height, {x, y}));
    return id;
}

bool Model::Entities::Level::intersects(const Model::Shape::Rectangle & rect) const
{
    for (const auto & terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().::sf::FloatRect::intersects(rect)) {
            return true;
        }
    }
    return false;
}

bool Model::Entities::Level::intersects(const Model::Shape::Line & line) const
{
    for (const auto & terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().intersects(line)) {
            return true;
        }
    }
    return false;
}

Model::DataStructures::RectGraph Model::Entities::Level::getCornerRectGraph(float width, float height) const
{
    return Model::DataStructures::RectGraph(width, height, *this);
}

Model::DataStructures::RectGraph Model::Entities::Level::buildCornerRectGraphWithPlayer(
    float width, float height, const Model::Entities::Player & player) const
{
    auto graph = getCornerRectGraph(width, height);
    graph.addTarget(player.getShape(), *this, 0.9f);
    return graph;
}
