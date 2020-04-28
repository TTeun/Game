#include "rectgraph.h"

#include "../../Aux/mathtools.h"
#include "../../View/window.h"
#include "level.h"

#include <cassert>

RectGraph::RectGraph(float width, float height, const Entities::Level & level)
{
    std::vector<sf::FloatRect> terrainRectangles;
    terrainRectangles.reserve(level.getTerrainBlocks().size());
    for (const auto & terrainBlock : level.getTerrainBlocks()) {
        terrainRectangles.emplace_back(terrainBlock->getShape());
    }

    for (const auto & terrainRectangle : terrainRectangles) {
        const auto position = sf::Vector2f(terrainRectangle.left, terrainRectangle.top);
        const auto size     = sf::Vector2f(terrainRectangle.width, terrainRectangle.height);

        m_rectangles.push_back(
            Rectangle(sf::FloatRect(position - sf::Vector2f(width, height), {width, height})).shrink(0.999f));
        m_rectangles.push_back(Rectangle(sf::FloatRect(position + size, {width, height})).shrink(0.999f));
        m_rectangles.push_back(
            Rectangle(sf::FloatRect(position + sf::Vector2f{size.x, -height}, {width, height})).shrink(0.999f));
        m_rectangles.push_back(
            Rectangle(sf::FloatRect(position + sf::Vector2f{-width, size.y}, {width, height})).shrink(0.999f));
    }

    for (auto it = m_rectangles.begin(); it != m_rectangles.end();) {
        if (level.interSects(*it)) {
            it = m_rectangles.erase(it);
        } else {
            ++it;
        }
    }

    for (size_t i = 0; i != m_rectangles.size() - 1; ++i) {
        const auto & rect1 = m_rectangles.at(i);
        for (size_t j = i + 1; j != m_rectangles.size(); ++j) {
            const auto & rect2 = m_rectangles.at(j);

            if (not rect1.isMutuallyFullyVisible(rect2, level)) {
                continue;
            } else {
                m_edges.insert({{i, j}, rect1.getDistance(rect2)});
            }
        }
    }
}

void RectGraph::draw(View::Window & window) const
{
    for (const auto & rectangle : m_rectangles) {
        window.drawRectangle(rectangle);
    }
    if (m_target) {
        window.drawRectangle(*m_target);
        for (auto i : m_edgesToTarget) {
            window.drawLine(m_rectangles.at(i.first).getCenter(),
                            m_target->getCenter(),
                            {255,
                             static_cast<sf::Uint8>(MathTools::clamp(0.3f * i.second, 0, 255)),
                             static_cast<sf::Uint8>(255 - MathTools::clamp(0.3f * i.second, 0, 255))});
        }
    }

    for (const auto & edge : m_edges) {
        window.drawLine(m_rectangles.at(edge.first.first).getCenter(),
                        m_rectangles.at(edge.first.second).getCenter(),
                        {100, 100, 100});
    }
}

void RectGraph::addTarget(const Rectangle & targetRectangle, const Entities::Level & level, float shrinkFactor)
{
    shrinkFactor = 1.0f;
    if (m_rectangles.empty()) {
        return;
    }

    m_edgesToTarget.clear();

    auto * shrunkTargetRectangle = new Rectangle(targetRectangle.shrink(shrinkFactor));
    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        const auto & rect1 = m_rectangles.at(i);

        if (not rect1.isMutuallyFullyVisible(*shrunkTargetRectangle, level)) {
            continue;
        } else {
            m_edgesToTarget.insert({i, shrunkTargetRectangle->getDistance(rect1)});
        }
    }
    m_target.reset(shrunkTargetRectangle);
}

sf::Vector2f
RectGraph::findDirectionToTarget(const Rectangle & rectangle, const Entities::Level & level, float shrinkFactor) const
{
    shrinkFactor = 1.0f;

    if (m_rectangles.empty()) {
        return {0.0f, 0.0f};
    }
    struct DijkstraInfo {
        size_t m_index;
        float m_dist       = std::numeric_limits<float>::max();
        size_t m_prevIndex = std::numeric_limits<size_t>::max();
        bool m_wasAdded    = false;
    };

    std::vector<DijkstraInfo> indices;
    indices.reserve(m_rectangles.size());
    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        indices.push_back({i, std::numeric_limits<float>::max(), std::numeric_limits<size_t>::max(), false});
    }

    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        if (isNeighborOfTarget(i)) {
            indices[i].m_dist      = m_edgesToTarget.at(i);
            indices[i].m_prevIndex = m_rectangles.size();
        }
    }

    while (true) {
        // Find index with smallest distance that is not yet added
        size_t minIndex = std::numeric_limits<size_t>::max();
        float minDist   = std::numeric_limits<float>::max();
        for (size_t i = 0; i != m_rectangles.size(); ++i) {
            if (not indices[i].m_wasAdded) {
                if (indices[i].m_dist <= minDist) {
                    minDist  = indices[i].m_dist;
                    minIndex = i;
                }
            }
        }

        if (minIndex == std::numeric_limits<size_t>::max()) {
            break;
        }

        assert(minIndex < m_rectangles.size());
        indices[minIndex].m_wasAdded = true;

        for (size_t i = 0; i != m_rectangles.size(); ++i) {
            if (not isNeighbor(i, minIndex)) {
                continue;
            }

            std::pair<size_t, size_t> edgePair =
                std::pair<size_t, size_t>(std::min(i, minIndex), std::max(i, minIndex));

            const float alt = indices[minIndex].m_dist + m_edges.at(edgePair);
            if (alt < indices[i].m_dist) {
                indices[i].m_dist      = alt;
                indices[i].m_prevIndex = minIndex;
            }
        }
    }

    const Rectangle shrunkRectangle = Rectangle(rectangle.shrink(shrinkFactor));
    std::map<size_t, float> edgesToRectangle;

    for (size_t i = 0; i != m_rectangles.size(); ++i) {
        const auto & rect1 = m_rectangles.at(i);
        if (level.interSects(Line{rect1.topRight(), shrunkRectangle.topRight()}) ||
            level.interSects(Line{rect1.topLeft(), shrunkRectangle.topLeft()}) ||
            level.interSects(Line{rect1.bottomRight(), shrunkRectangle.bottomRight()}) ||
            level.interSects(Line{rect1.bottomLeft(), shrunkRectangle.bottomLeft()})) {
            continue;
        } else {
            edgesToRectangle.insert({i, rect1.getDistance(shrunkRectangle)});
        }
    }

    size_t minIndex = std::numeric_limits<size_t>::max();
    float minDist   = std::numeric_limits<float>::max();
    if (m_target->isMutuallyFullyVisible(shrunkRectangle, level)) {
        minIndex = m_rectangles.size();
        minDist  = m_target->getDistance(shrunkRectangle);
    }

    for (const auto & it : edgesToRectangle) {
        if (indices[it.first].m_dist + it.second < minDist) {
            minDist  = indices[it.first].m_dist + it.second;
            minIndex = it.first;
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

bool RectGraph::isNeighborOfTarget(size_t i) const
{
    return m_edgesToTarget.find(i) != m_edgesToTarget.end();
}

bool RectGraph::isNeighbor(size_t i, size_t j) const
{
    if (j < i) {
        return isNeighbor(j, i);
    }
    return (m_edges.find({i, j}) != m_edges.end() || m_edges.find({j, i}) != m_edges.end());
}
