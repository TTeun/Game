//
// Created by pc on 4/28/20.
//

#ifndef TEUN_GAME_RECTGRAPH_H
#define TEUN_GAME_RECTGRAPH_H

#include "../../View/drawable.h"
#include "../Geometry/rectangle.h"

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
} // namespace Model

namespace Model {
    namespace DataStructures {

        class RectGraph : public View::Drawable {

        public:
            RectGraph(float width, float height, const Entities::LevelWrapper & levelWrapper);

            void draw(View::Window & window) const override;

            void addTarget(const Geometry::Rectangle & targetRectangle,
                           const Entities::LevelWrapper & levelWrapper,
                           float shrinkFactor);

            Model::Geometry::Point findDirectionToTarget(const Geometry::Rectangle & rectangle,
                                                         const Model::Entities::LevelWrapper & levelWrapper,
                                                         float shrinkFactor) const;

            bool hasTarget() const;

            const std::map<std::pair<size_t, size_t>, float> & getEdges() const;

            const std::vector<Geometry::Rectangle> & getRectangles() const;

            const std::map<size_t, float> & getEdgesToTarget() const;

            const std::unique_ptr<Geometry::Rectangle> & getTarget() const;

        private:
            struct DijkstraInfo {
                DijkstraInfo(size_t index) : m_index(index)
                {
                }

                size_t m_index;
                float m_dist       = std::numeric_limits<float>::max();
                size_t m_prevIndex = std::numeric_limits<size_t>::max();
                bool m_wasAdded    = false;
            };

            std::vector<DijkstraInfo> buildDijkstraVertices() const;

            std::vector<DijkstraInfo> createEmptyDijkstraVertices() const;

            void addDijkstraEdgesToTarget(std::vector<DijkstraInfo> & dijkstraVertices) const;

            std::pair<size_t, float> findClosestNotYetAdded(const std::vector<DijkstraInfo> &) const;

            std::map<std::pair<size_t, size_t>, float> m_edges;

            std::vector<Geometry::Rectangle> m_rectangles;

            std::map<size_t, float> m_edgesToTarget;

            std::unique_ptr<Geometry::Rectangle> m_target;

            std::vector<std::vector<size_t>> m_edgeArray;

            bool isNeighbor(size_t i, size_t j) const;

            bool isNeighborOfTarget(size_t i) const;
        };

    } // namespace DataStructures
} // namespace Model

#endif // TEUN_GAME_RECTGRAPH_H
