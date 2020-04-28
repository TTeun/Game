//
// Created by pc on 4/26/20.
//

#ifndef SFML_DRAWINTERFACE_H
#define SFML_DRAWINTERFACE_H

#include "tilemap.h"

#include <list>
#include <map>
#include <memory>

namespace Model {
    class Model;

    class Loaders;
} // namespace Model

namespace Entities {
    class Level;

    class EntityList;

    class DebrisExplosion;

    class Enemy;

    class Player;

} // namespace Entities

namespace View {

    class Window;

    class DrawInterface {

        friend class Model::Loaders;

    public:
        void drawModel(Window & window, const Model::Model & model);

    private:
        std::map<size_t, std::unique_ptr<const TileMap>> m_levelTileMaps;

        void addLevelTileMap(size_t id, const TileMap * tileMap);

        void drawLevel(Window & window, const Entities::Level & terrain, const sf::FloatRect & viewRect);

        void
        drawEntities(View::Window & window, const Entities::EntityList & entityList, const sf::FloatRect & viewRect);

        void drawDebrisExplosions(Window & window,
                                  const std::list<Entities::DebrisExplosion> & debrisExplosionList,
                                  const sf::FloatRect & viewRect);

        void drawEnemies(Window & window, const std::list<Entities::Enemy> & enemyList, const sf::FloatRect & viewRect);

        void drawPlayer(Window & window, const Entities::Player & player);
    };
} // namespace View

#endif // SFML_DRAWINTERFACE_H
