#ifndef TEUN_GAME_ENTITYCONTROLLER_H
#define TEUN_GAME_ENTITYCONTROLLER_H

#include "../../colors.h"
#include "debrisexplosion.h"
#include "enemy.h"
#include "levelwrapper.h"
#include "player.h"
#include "water.h"

#include <list>
#include <memory>

namespace Controller {
    class KeyBoardHandler;
}

namespace Model {
    namespace DataStructures {
        class RectGraph;
    }

    namespace Entities {

        class EntityController : public View::Drawable {

            friend class Controller::KeyBoardHandler;

        public:
            EntityController();

            void draw(View::Window & window) const override;

            const Entities::LevelWrapper & getLevelWrapper() const;

            Entities::LevelWrapper & getLevelWrapper();

            const std::list<Entities::DebrisExplosion> & getDebrisExplosions() const;

            const std::list<Entities::Enemy> & getEnemies() const;

            void addDebrisExplosion();

            void addEnemy(const Geometry::Point & position);

            void update(float dt, const Physics::Constants & constants);

            void setLevel(std::unique_ptr<Entities::Level> level);

            void handleAi(float dt);

            const Entities::Player & getPlayer() const;

            const Water & getWater() const;

            void addPlayer(float x                 = 200.0f,
                           float y                 = 230.0f,
                           float width             = 25,
                           float height            = 25,
                           const sf::Color & color = Colors::playerColor);

        private:
            Entities::Player & getPlayer();

            std::list<Entities::DebrisExplosion> m_debrisExplosionVector;

            std::list<Entities::Enemy> m_enemyVector;

            std::unique_ptr<Entities::Player> m_player;

            std::unique_ptr<Entities::LevelWrapper> m_levelWrapper;

            std::unique_ptr<Water> m_water;
        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_ENTITYCONTROLLER_H
