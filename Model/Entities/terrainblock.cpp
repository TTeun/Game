//
// Created by pc on 4/26/20.
//

#include "terrainblock.h"

Model::Entities::TerrainBlock::TerrainBlock(const size_t id,
                                            float width,
                                            float height,
                                            const Geometry::Point & position)
    : Physics::Object(Model::Geometry::ColoredRectangle({width, height}, position)), m_id(id)
{
}

size_t Model::Entities::TerrainBlock::getId() const
{
    return m_id;
}

Model::Entities::TerrainBlock::TerrainBlock(size_t id, Model::Geometry::ColoredRectangle && coloredRectangle)
    : Physics::Object(std::move(coloredRectangle)), m_id(id)
{
}
