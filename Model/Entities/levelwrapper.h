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

            void setLevel(std::unique_ptr<Entities::Level> level);

            const Level &getLevel() const;

            size_t addTerrainBlock(float x, float y, float width, float height);

            bool intersects(const Shape::Line &line) const;

            bool intersects(const Shape::Rectangle &rect) const;


            Model::DataStructures::RectGraph getCornerRectGraph(float width, float height) const;

            Model::DataStructures::RectGraph buildCornerRectGraphWithPlayer(
                    float width, float height, const Model::Entities::Player &player) const;


        private:

            Level &getLevel();

            std::unique_ptr<Entities::Level> m_level;
        };

    }
}


#endif //TEUN_GAME_LEVELWRAPPER_H
