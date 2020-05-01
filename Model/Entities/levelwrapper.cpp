//
// Created by pc on 4/29/20.
//

#include "levelwrapper.h"

#include <memory>

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

const Model::Entities::Level &Model::Entities::LevelWrapper::getLevel() const {
    return *m_level;
}

Model::Entities::Level &Model::Entities::LevelWrapper::getLevel() {
    return *m_level;
}

bool Model::Entities::LevelWrapper::intersects(const Model::Shapes::Line &line) const {
    return m_level->intersects(line);
}

bool Model::Entities::LevelWrapper::intersects(const Model::Shapes::Rectangle &rect) const {
    return m_level->intersects(rect);
}

void Model::Entities::LevelWrapper::initLevelWrapperWithLevel(std::unique_ptr<Entities::Level> level) {
    m_level = std::move(level);
}

const Model::DataStructures::RectGraph &Model::Entities::LevelWrapper::getCornerRectGraph() const{
    return *m_cornerRectGraph;
}

void Model::Entities::LevelWrapper::setCornerRectGraph(float width, float height) {
    m_cornerRectGraph = std::make_unique<Model::DataStructures::RectGraph>(width, height, *this);
}

void Model::Entities::LevelWrapper::addPlayerToCornerRectGraph(const Model::Entities::Player &player) {
    assert(m_cornerRectGraph);
    m_cornerRectGraph->addTarget(player.getShape(), *this, 1.0f);
}

const Model::DataStructures::RectGraph &Model::Entities::LevelWrapper::getCornerRectGraphWithTarget() const {
    assert(m_cornerRectGraph);
    assert(m_cornerRectGraph->hasTarget());
    return *m_cornerRectGraph;
}
