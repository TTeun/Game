//
// Created by pc on 4/29/20.
//

#include "levelwrapper.h"

#include "player.h"

const Model::Entities::Level & Model::Entities::LevelWrapper::getLevel() const
{
    assert(m_level);
    return *m_level;
}

bool Model::Entities::LevelWrapper::intersects(const Model::Geometry::Line & line) const
{
    return getLevel().intersects(line);
}

bool Model::Entities::LevelWrapper::intersects(const Model::Geometry::Rectangle & rect) const
{
    return getLevel().intersects(rect);
}

void Model::Entities::LevelWrapper::initLevelWrapperWithLevel(std::unique_ptr<Entities::Level> level)
{
    m_level = std::move(level);
    setCornerRectGraph(40, 40);
}

const Model::DataStructures::RectGraph & Model::Entities::LevelWrapper::getCornerRectGraph() const
{
    assert(m_cornerRectGraph);
    return *m_cornerRectGraph;
}

void Model::Entities::LevelWrapper::setCornerRectGraph(float width, float height)
{
    m_cornerRectGraph = std::make_unique<Model::DataStructures::RectGraph>(width, height, *this);
}

void Model::Entities::LevelWrapper::addPlayerToCornerRectGraph(const Model::Entities::Player & player)
{
    assert(m_cornerRectGraph);
    m_cornerRectGraph->addTarget(player.getShape(), *this, 1.0f);
}
