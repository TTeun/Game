//
// Created by pc on 4/29/20.
//

#ifndef TEUN_GAME_AI_H
#define TEUN_GAME_AI_H

namespace Model {
    namespace Entities {
        class EntityController;

        class Ai {

        protected:
            virtual void handleAi(float dt, const Model::Entities::EntityController & entityController) = 0;
        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_AI_H
