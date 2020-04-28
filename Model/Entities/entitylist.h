//
// Created by pc on 4/26/20.
//

#ifndef GAME_ENTITYLIST_H
#define GAME_ENTITYLIST_H

#include "debrisexplosion.h"
#include "enemy.h"
#include "level.h"
#include "player.h"

#include <list>
#include <memory>

namespace Controller {
    class KeyBoardHandler;
}

class RectGraph;

namespace Entities {

    class EntityList {

        friend class Controller::KeyBoardHandler;

    public:
        EntityList();

        const Level & getLevel() const;

        const std::list<DebrisExplosion> & getDebrisExplosions() const;

        const std::list<Enemy> & getEnemies() const;

        void addDebrisExplosion();

        void addEnemy(const sf::Vector2f & position);

        void update(float dt, const Physics::Constants & constants);

        void setLevel(Level * level);

        void handleAi(float dt, const RectGraph & rectGraph);

        const Player & getPlayer() const;

        Player & getPlayer();

    private:
        std::list<DebrisExplosion> m_debrisExplosionVector;

        std::list<Enemy> m_enemyVector;

        Player m_player = Player(200, 230, 25, 25, Colors::playerColor);

        std::unique_ptr<Level> m_level;
    };

} // namespace Entities

#endif // GAME_ENTITYLIST_H
