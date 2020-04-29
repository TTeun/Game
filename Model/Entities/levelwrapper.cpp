//
// Created by pc on 4/29/20.
//

#include "levelwrapper.h"

#include "player.h"

Model::DataStructures::RectGraph Model::Entities::LevelWrapper::getCornerRectGraph(float width, float height) const {
    return Model::DataStructures::RectGraph(width, height, *this);
}

Model::DataStructures::RectGraph
Model::Entities::LevelWrapper::buildCornerRectGraphWithPlayer(float width, float height,
                                                              const Model::Entities::Player &player) const {
    auto graph = getCornerRectGraph(width, height);
    graph.addTarget(player.getShape(), *this, 0.9f);
    return graph;
}

size_t Model::Entities::LevelWrapper::addTerrainBlock(float x, float y, float width, float height) {
    return m_level->addTerrainBlock(x, y, width, height);
}

const Model::Entities::Level &Model::Entities::LevelWrapper::getLevel() const {
    return *m_level;
}

Model::Entities::Level &Model::Entities::LevelWrapper::getLevel() {
    return *m_level;
}

bool Model::Entities::LevelWrapper::intersects(const Model::Shape::Line &line) const {
    return m_level->intersects(line);
}

bool Model::Entities::LevelWrapper::intersects(const Model::Shape::Rectangle &rect) const {
    return m_level->intersects(rect);
}

void Model::Entities::LevelWrapper::setLevel(std::unique_ptr<Entities::Level> level) {
    m_level = std::move(level);
}
