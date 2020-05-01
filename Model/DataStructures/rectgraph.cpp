#include "rectgraph.h"

#include "../../Aux/mathtools.h"
#include "../../View/window.h"
#include "../../View/drawinterface.h"

#include <cassert>
#include <set>

Model::DataStructures::RectGraph::RectGraph(float width, float height, const Entities::LevelWrapper &levelWrapper) {
    std::vector<Model::Shapes::Rectangle> terrainRectangles;
    terrainRectangles.reserve(levelWrapper.getLevel().getTerrainBlocks().size());
    for (const auto &terrainBlock : levelWrapper.getLevel().getTerrainBlocks()) {
        terrainRectangles.emplace_back(terrainBlock->getShape());
    }

    const auto sizeOfObject = Model::Shapes::Point(width, height);
    for (const auto &terrainRectangle : terrainRectangles) {
        const auto position = terrainRectangle.topLeft();
        const auto size = terrainRectangle.getSize();

        m_rectangles.push_back(
                Shapes::Rectangle(sizeOfObject, position - sizeOfObject).shrink(
                        0.999f));
        m_rectangles.push_back(Shapes::Rectangle(sizeOfObject, position + size).shrink(0.999f));
        m_rectangles.push_back(
                Shapes::Rectangle(sizeOfObject, position + Model::Shapes::Point{size.x, -height}).shrink(
                        0.999f));
        m_rectangles.push_back(
                Shapes::Rectangle(sizeOfObject, position + Model::Shapes::Point{-width, size.y}).shrink(
                        0.999f));
    }

    for (auto it = m_rectangles.begin(); it != m_rectangles.end();) {
        if (levelWrapper.intersects(*it)) {
            it = m_rectangles.erase(it);
        } else {
            ++it;
        }
    }

    for (size_t i = 0; i != m_rectangles.size() - 1; ++i) {
        const auto &rect1 = m_rectangles.at(i);
        for (size_t j = i + 1; j != m_rectangles.size(); ++j) {
            const auto &rect2 = m_rectangles.at(j);

            if (not rect1.isMutuallyFullyVisible(rect2, levelWrapper)) {
                continue;
            } else {
                m_edges.insert({{i, j}, rect1.getDistance(rect2)});
            }
        }
    }

    m_edgeArray.resize(m_rectangles.size());
    for (const auto &it : m_edges) {
        m_edgeArray[it.first.first].push_back(it.first.second);
    }

}

void Model::DataStructures::RectGraph::draw(View::Window &window) const {
    View::DrawInterface::draw(*this, window);
}

void Model::DataStructures::RectGraph::addTarget(const Shapes::Rectangle &targetRectangle,
                                                 const Entities::LevelWrapper &levelWrapper,
                                                 float shrinkFactor) {
    shrinkFactor = 1.0f;
    if (m_rectangles.empty()) {
        return;
    }

    m_edgesToTarget.clear();

    auto *shrunkTargetRectangle = new Shapes::Rectangle(targetRectangle.shrink(shrinkFactor));
    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        const auto &rect1 = m_rectangles.at(i);

        if (not rect1.isMutuallyFullyVisible(*shrunkTargetRectangle, levelWrapper)) {
            continue;
        } else {
            m_edgesToTarget.insert({i, shrunkTargetRectangle->getDistance(rect1)});
        }
    }
    m_target.reset(shrunkTargetRectangle);
}

Model::Shapes::Point Model::DataStructures::RectGraph::findDirectionToTarget(const Shapes::Rectangle &rectangle,
                                                                             const Entities::LevelWrapper &levelWrapper,
                                                                             float shrinkFactor) const {
    // ToDo omdat anders de vijanden kleiner worden en eigenlijk niet passen!
    shrinkFactor = 1.0f;

    if (not hasTarget() || m_edgesToTarget.empty() || m_rectangles.empty()) {

        return {0.0f, 0.0f};
    }

    auto dijkstraVertices = buildDijkstraVertices();

    const Shapes::Rectangle shrunkRectangle = Shapes::Rectangle(rectangle.shrink(shrinkFactor));

    std::map<size_t, float> edgesToRectangle;
    size_t minIndex = std::numeric_limits<size_t>::max();
    float minDist = std::numeric_limits<float>::max();

    if (m_target->isMutuallyFullyVisible(shrunkRectangle, levelWrapper)) {
        minIndex = m_rectangles.size();
        minDist = m_target->getDistance(shrunkRectangle);
    }

    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        const auto &rect1 = m_rectangles.at(i);
        if (not rect1.isMutuallyFullyVisible(shrunkRectangle, levelWrapper)) {
            continue;
        } else {
            const float dist = rect1.getDistance(shrunkRectangle);
            if (dijkstraVertices[i].m_dist + dist < minDist) {
                minDist = dijkstraVertices[i].m_dist + dist;
                minIndex = i;
            }
        }
    }

    if (minIndex == m_rectangles.size()) {
        return (m_target->getCenter() - shrunkRectangle.getCenter());
    } else {
        if (minIndex == std::numeric_limits<size_t>::max()) {
            return {0.0f, 0.0f};
        }
        return (m_rectangles.at(minIndex).getCenter() - shrunkRectangle.getCenter());
    }
}

bool Model::DataStructures::RectGraph::isNeighborOfTarget(size_t i) const {
    return m_edgesToTarget.find(i) != m_edgesToTarget.end();
}

bool Model::DataStructures::RectGraph::isNeighbor(size_t i, size_t j) const {
    if (j < i) {
        return isNeighbor(j, i);
    }
    return (m_edges.find({i, j}) != m_edges.end() || m_edges.find({j, i}) != m_edges.end());
}


std::vector<Model::DataStructures::RectGraph::DijkstraInfo>
Model::DataStructures::RectGraph::buildDijkstraVertices() const {

    auto dijkstraVertices = createEmptyDijkstraVertices();
    addDijkstraEdgesToTarget(dijkstraVertices);

    while (true) {
        // Find index with smallest distance that is not yet added
        auto[minIndex, minDist] = findClosestNotYetAdded(dijkstraVertices);

        if (minIndex == std::numeric_limits<size_t>::max()) {
            // Alle vertices bekeken!
            break;
        }

        assert(minIndex < m_rectangles.size());
        dijkstraVertices[minIndex].m_wasAdded = true;

        for (auto i : m_edgeArray.at(minIndex)) {
            std::pair<size_t, size_t> edgePair =
                    std::make_pair(std::min(i, minIndex), std::max(i, minIndex));

            const float alt = dijkstraVertices[minIndex].m_dist + m_edges.at(edgePair);
            if (alt < dijkstraVertices[i].m_dist) {
                dijkstraVertices[i].m_dist = alt;
                dijkstraVertices[i].m_prevIndex = minIndex;
            }
        }
    }
    return dijkstraVertices;
}

void Model::DataStructures::RectGraph::addDijkstraEdgesToTarget(
        std::vector<Model::DataStructures::RectGraph::DijkstraInfo> &dijkstraVertices) const {
    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        if (isNeighborOfTarget(i)) {
            dijkstraVertices[i].m_dist = m_edgesToTarget.at(i);
            dijkstraVertices[i].m_prevIndex = m_rectangles.size();
        }
    }

}

std::vector<Model::DataStructures::RectGraph::DijkstraInfo>
Model::DataStructures::RectGraph::createEmptyDijkstraVertices() const {
    std::vector<DijkstraInfo> dijkstraVertices;
    dijkstraVertices.reserve(m_rectangles.size());
    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        dijkstraVertices.emplace_back(i);
    }
    return dijkstraVertices;
}

std::pair<size_t, float>
Model::DataStructures::RectGraph::findClosestNotYetAdded(
        const std::vector<Model::DataStructures::RectGraph::DijkstraInfo> &dijkstraVertices) const {
    size_t minIndex = std::numeric_limits<size_t>::max();
    float minDist = std::numeric_limits<float>::max();
    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        if (not dijkstraVertices[i].m_wasAdded) {
            if (dijkstraVertices[i].m_dist <= minDist) {
                minDist = dijkstraVertices[i].m_dist;
                minIndex = i;
            }
        }
    }
    return {minIndex, minDist};
}

const std::map<std::pair<size_t, size_t>, float> &Model::DataStructures::RectGraph::getEdges() const {
    return m_edges;
}

const std::vector<Model::Shapes::Rectangle> &Model::DataStructures::RectGraph::getRectangles() const {
    return m_rectangles;
}

const std::map<size_t, float> &Model::DataStructures::RectGraph::getEdgesToTarget() const {
    return m_edgesToTarget;
}

const std::unique_ptr<Model::Shapes::Rectangle> &Model::DataStructures::RectGraph::getTarget() const {
    return m_target;
}
