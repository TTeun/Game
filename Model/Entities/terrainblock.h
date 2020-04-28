//
// Created by pc on 4/26/20.
//

#ifndef SFML_TERRAINBLOCK_H
#define SFML_TERRAINBLOCK_H

#include "../Physics/object.h"
#include "../Shape/rectangle.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace View {
    class Window;
}

namespace Model {

    namespace Entities {

        class TerrainBlock : public Physics::Object {
        public:
            TerrainBlock(size_t id, float width, float height, const sf::Vector2f & position);

            size_t getId() const;

        private:
            const size_t m_id;
        };
    } // namespace Entities
} // namespace Model
#endif // SFML_TERRAINBLOCK_H
