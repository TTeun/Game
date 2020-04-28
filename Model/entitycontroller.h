#ifndef GAME_ENTITYLIST_H
#define GAME_ENTITYLIST_H

#include "../colors.h"
#include "Entities/debrisexplosion.h"
#include "Entities/enemy.h"
#include "Entities/level.h"
#include "Entities/player.h"

#include <list>
#include <memory>

namespace Controller {
    class KeyBoardHandler;
}

namespace Model {
    namespace DataStructures {
        class RectGraph;
    }

    class EntityController {

        friend class Controller::KeyBoardHandler;

    public:
        EntityController();

        const Entities::Level & getLevel() const;

        const std::list<Entities::DebrisExplosion> & getDebrisExplosions() const;

        const std::list<Entities::Enemy> & getEnemies() const;

        void addDebrisExplosion();

        void addEnemy(const sf::Vector2f & position);

        void update(float dt, const Physics::Constants & constants);

        void setLevel(std::unique_ptr<Entities::Level> level);

        void handleAi(float dt, const DataStructures::RectGraph & rectGraph);

        const Entities::Player & getPlayer() const;

    private:
        Entities::Player & getPlayer();

        std::list<Entities::DebrisExplosion> m_debrisExplosionVector;

        std::list<Entities::Enemy> m_enemyVector;

        Entities::Player m_player = Entities::Player(200, 230, 25, 25, Colors::playerColor);

        std::unique_ptr<Entities::Level> m_level;
    };
} // namespace Model

#endif // GAME_ENTITYLIST_H
