//
// Created by pc on 4/28/20.
//

#ifndef TEUN_GAME_RECTGRAPH_H
#define TEUN_GAME_RECTGRAPH_H

#include "../Shape/rectangle.h"

#include <map>
#include <memory>
#include <vector>

namespace View {
    class Window;
}

namespace Model {
    namespace Entities {
        class LevelWrapper;
    }
}

namespace Model {
    namespace DataStructures {

        class RectGraph {

        public:
            RectGraph(float width, float height, const Entities::LevelWrapper &levelWrapper);

            void draw(View::Window &window) const;

            void addTarget(const Shape::Rectangle &targetRectangle, const Entities::LevelWrapper &levelWrapper, float shrinkFactor);

            Model::Shape::Point findDirectionToTarget(const Shape::Rectangle &rectangle,
                                                      const Model::Entities::LevelWrapper &levelWrapper,
                                                      float shrinkFactor) const;

        private:
            std::map<std::pair<size_t, size_t>, float> m_edges;

            std::vector<Shape::Rectangle> m_rectangles;

            std::map<size_t, float> m_edgesToTarget;

            std::unique_ptr<Shape::Rectangle> m_target;

            bool isNeighbor(size_t i, size_t j) const;

            bool isNeighborOfTarget(size_t i) const;
        };

    } // namespace DataStructures
} // namespace Model

#endif // TEUN_GAME_RECTGRAPH_H
