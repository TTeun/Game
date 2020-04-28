//
// Created by pc on 4/28/20.
//

#ifndef SFML_RECTGRAPH_H
#define SFML_RECTGRAPH_H

#include "Shape/rectangle.h"

#include <map>
#include <memory>
#include <vector>

namespace View {
    class Window;
}

namespace Entities {
    class Level;
}

class RectGraph {

public:
    RectGraph(float width, float height, const Entities::Level & level);

    void draw(View::Window & window) const;

    void addTarget(const Rectangle & targetRectangle, const Entities::Level & level, float shrinkFactor);

    sf::Vector2f
    findDirectionToTarget(const Rectangle & rectangle, const Entities::Level & level, float shrinkFactor) const;

private:
    std::map<std::pair<size_t, size_t>, float> m_edges;

    std::vector<Rectangle> m_rectangles;

    std::map<size_t, float> m_edgesToTarget;

    std::unique_ptr<Rectangle> m_target;

    bool isNeighbor(size_t i, size_t j) const;

    bool isNeighborOfTarget(size_t i) const;
};

#endif // SFML_RECTGRAPH_H
