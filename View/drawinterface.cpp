//
// Created by pc on 4/26/20.
//

#include "drawinterface.h"

#include "../Model/entitycontroller.h"
#include "window.h"

#include <iostream>

void View::DrawInterface::drawLevel(View::Window & window,
                                    const Model::Entities::Level & terrain,
                                    const sf::FloatRect & viewRect)
{
    const auto & terrainBlocks = terrain.getTerrainBlocks();
    for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
        assert(m_levelTileMaps.find((*it)->getId()) != m_levelTileMaps.end());
        const auto & shape = (**it).getShape();
        if (not shape.intersects(viewRect)) {
            continue;
        }
        const auto & tileMap = m_levelTileMaps.at((*it)->getId());
        if (tileMap) {
            window.drawRectangle(shape);
            window.draw(*m_levelTileMaps.at((*it)->getId()));
        } else {
            window.drawRectangle((**it).getShape());
        }
    }
}

void View::DrawInterface::drawPlayer(View::Window & window, const Model::Entities::Player & player)
{
    window.drawRectangle(player.getShape());
}

void View::DrawInterface::drawDebrisExplosions(View::Window & window,
                                               const std::list<Model::Entities::DebrisExplosion> & debrisExplosionList,
                                               const sf::FloatRect & viewRect)
{
    for (const auto & explosion : debrisExplosionList) {
        for (const auto & debris : explosion.getDebrisVector()) {
            //            if (not debris.getShape().intersects(viewRect)) {
            //                continue;
            //            }
            window.drawRectangle(debris.getShape());
        }
    }
}

void View::DrawInterface::drawEnemies(Window & window,
                                      const std::list<Model::Entities::Enemy> & enemyList,
                                      const sf::FloatRect & viewRect)
{
    for (const auto & enemy : enemyList) {
        if (not enemy.getShape().::sf::FloatRect::intersects(viewRect)) {
            continue;
        }

        window.drawRectangle(enemy.getShape());
    }
}

void View::DrawInterface::drawEntities(View::Window & window,
                                       const Model::EntityController & entityList,
                                       const sf::FloatRect & viewRect)
{
    drawLevel(window, entityList.getLevel(), viewRect);
    drawPlayer(window, entityList.getPlayer());
    drawDebrisExplosions(window, entityList.getDebrisExplosions(), viewRect);
    drawEnemies(window, entityList.getEnemies(), viewRect);
}

void View::DrawInterface::drawModel(View::Window & window, const Model::EntityController & model)
{
    const sf::FloatRect & rect = window.getViewRect();

    drawEntities(window, model, rect);
}

void View::DrawInterface::addLevelTileMap(size_t id, const TileMap * tileMap)
{
    assert(m_levelTileMaps.find(id) == m_levelTileMaps.end());
    m_levelTileMaps.insert(std::pair<size_t, std::unique_ptr<const TileMap>>(id, tileMap));
}
