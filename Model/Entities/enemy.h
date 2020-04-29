//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_ENEMY_H
#define TEUN_GAME_ENEMY_H

#include "../Physics/intersectableobject.h"
#include "ai.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Model {

    namespace Entities {

        class Enemy : public Physics::IntersectableObject, public Model::Entities::Ai {
        public:
            static Enemy create(const sf::Vector2f &position);

        protected:
            void handleAi(float dt, const EntityController &entityController) override;

        private:
            Enemy(const sf::Vector2f &size, const sf::Vector2f &position);

            size_t m_myvalue;
        };


    } // namespace Entities

} // namespace Model
#endif // TEUN_GAME_ENEMY_H
