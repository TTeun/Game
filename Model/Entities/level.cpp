//
// Created by pc on 4/26/20.
//

#include "level.h"
#include "../../View/drawinterface.h"

Model::Entities::Level::Level() {
}

const std::list<std::unique_ptr<Model::Entities::TerrainBlock>> &Model::Entities::Level::getTerrainBlocks() const {
    return m_terrainBlocks;
}

size_t Model::Entities::Level::addTerrainBlock(Model::Shapes::ColoredRectangle &&coloredRectangle) {
    const size_t id = m_terrainBlocks.size();
    m_terrainBlocks.emplace_back(new TerrainBlock(id, std::move(coloredRectangle)));
    return id;
}

bool Model::Entities::Level::intersects(const Model::Shapes::Rectangle &rect) const {
    for (const auto &terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().intersects(rect)) {
            return true;
        }
    }
    return false;
}

bool Model::Entities::Level::intersects(const Model::Shapes::Line &line) const {
    for (const auto &terrainBlock : m_terrainBlocks) {
        if (terrainBlock->getShape().intersects(line)) {
            return true;
        }
    }
    return false;
}

void Model::Entities::Level::draw(View::Window &window) const {
    View::DrawInterface::draw(*this, window);
}
