//
// Created by pc on 4/26/20.
//

#include "terrainblock.h"

TerrainBlock::TerrainBlock(const size_t id, float width, float height, const sf::Vector2f & position)
    : Physics::Object(Rectangle({width, height}, position)), m_id(id)
{
}

size_t TerrainBlock::getId() const
{
    return m_id;
}
