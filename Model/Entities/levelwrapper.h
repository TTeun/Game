//
// Created by pc on 4/29/20.
//

#ifndef TEUN_GAME_LEVELWRAPPER_H
#define TEUN_GAME_LEVELWRAPPER_H

#include "../DataStructures/rectgraph.h"
#include "level.h"

#include <memory>

namespace Model {
    namespace Entities {

        class Player;

        class LevelWrapper {

        public:
            void initLevelWrapperWithLevel(std::unique_ptr<Entities::Level> level);

            const Level & getLevel() const;

            bool intersects(const Geometry::Line & line) const;

            bool intersects(const Geometry::Rectangle & rect) const;

            void setCornerRectGraph(float width, float height);

            void addPlayerToCornerRectGraph(const Model::Entities::Player & player);

            const Model::DataStructures::RectGraph & getCornerRectGraph() const;

        private:
            std::unique_ptr<Entities::Level> m_level;

            std::unique_ptr<Model::DataStructures::RectGraph> m_cornerRectGraph;
        };

    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_LEVELWRAPPER_H
