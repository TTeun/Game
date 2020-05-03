//
// Created by pc on 4/26/20.
//

#include "level.h"

#include "../../View/drawinterface.h"

Model::Entities::Level::Level()
{
}

const std::list<std::unique_ptr<Model::Entities::TerrainBlock>> & Model::Entities::Level::getTerrainBlocks() const
{
    return m_terrainBlocks;
}

void Model::Entities::Level::addTerrainBlock(Model::Geometry::ColoredRectangle && coloredRectangle)
{
    m_terrainBlocks.emplace_back(new TerrainBlock(m_terrainBlocks.size(), std::move(coloredRectangle)));
}

bool Model::Entities::Level::intersects(const Model::Geometry::Rectangle & rect) const
{
    for (const auto & terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().intersects(rect)) {
            return true;
        }
    }
    return false;
}

bool Model::Entities::Level::intersects(const Model::Geometry::Line & line) const
{
    for (const auto & terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().intersects(line)) {
            return true;
        }
    }
    return false;
}

void Model::Entities::Level::draw(View::Window & window) const
{
    View::DrawInterface::draw(*this, window);
}
