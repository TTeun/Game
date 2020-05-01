//
// Created by pc on 4/29/20.
//

#ifndef TEUN_GAME_LEVELWRAPPER_H
#define TEUN_GAME_LEVELWRAPPER_H

#include "level.h"

namespace Model {
    namespace Entities {

        class LevelWrapper {

        public:

            void initLevelWrapperWithLevel(std::unique_ptr<Entities::Level> level);

            const Level &getLevel() const;

            bool intersects(const Shapes::Line &line) const;

            bool intersects(const Shapes::Rectangle &rect) const;

            Model::DataStructures::RectGraph getCornerRectGraph(float width, float height) const;

            void setCornerRectGraph(float width, float height);

            void addPlayerToCornerRectGraph(const Model::Entities::Player &player);

            const Model::DataStructures::RectGraph &getCornerRectGraphWithTarget() const;

            Model::DataStructures::RectGraph buildCornerRectGraphWithPlayer(
                    float width, float height, const Model::Entities::Player &player) const;

            const Model::DataStructures::RectGraph &getCornerRectGraph() const;

        private:

            Level &getLevel();

            std::unique_ptr<Entities::Level> m_level;

            std::unique_ptr<Model::DataStructures::RectGraph> m_cornerRectGraph;
        };

    }
}


#endif //TEUN_GAME_LEVELWRAPPER_H
