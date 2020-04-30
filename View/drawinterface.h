//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_DRAWINTERFACE_H
#define TEUN_GAME_DRAWINTERFACE_H

#include "tilemap.h"
#include "../Model/Entities/levelwrapper.h"

#include <list>
#include <map>
#include <memory>

namespace Model {
    class EntityController;

    class Loaders;
} // namespace Model

namespace Model {
    class EntityController;

    namespace Entities {
        class Level;

        class DebrisExplosion;

        class Enemy;

        class Player;

    } // namespace Entities

} // namespace Model

namespace View {

    class Window;

    class DrawInterface {

        friend class Model::Loaders;

    public:
        void drawModel(Window &window, const Model::EntityController &entityController);

    private:
        std::map<size_t, std::unique_ptr<const TileMap>> m_levelTileMaps;

        void addLevelTileMap(size_t id, const TileMap *tileMap);

        void
        drawLevel(Window &window, const Model::Entities::LevelWrapper &levelWrapper, const sf::FloatRect &viewRect);

        void
        drawEntities(View::Window &window, const Model::EntityController &entityController, const sf::FloatRect &viewRect);

        void drawDebrisExplosions(Window &window,
                                  const std::list<Model::Entities::DebrisExplosion> &debrisExplosionList,
                                  const sf::FloatRect &viewRect);

        void drawEnemies(Window &window,
                         const std::list<Model::Entities::Enemy> &enemyList,
                         const sf::FloatRect &viewRect);

        void drawPlayer(Window &window, const Model::Entities::Player &player);
    };
} // namespace View

#endif // TEUN_GAME_DRAWINTERFACE_H
