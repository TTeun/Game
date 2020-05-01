//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_LEVEL_H
#define TEUN_GAME_LEVEL_H

#include "../../View/drawable.h"
#include "terrainblock.h"

#include <list>
#include <memory>

class TiXmlElement;

namespace View {
    class Window;
}

namespace Model {

    class Loaders;

    namespace Entities {
        class Player;

        class Level : public View::Drawable {

            friend LevelWrapper;
            friend Loaders;

        public:
            Level();

            void draw(View::Window & window) const override;

            const std::list<std::unique_ptr<TerrainBlock>> & getTerrainBlocks() const;

        private:
            bool intersects(const Geometry::Line & line) const;

            bool intersects(const Geometry::Rectangle & rect) const;

            size_t addTerrainBlock(Model::Geometry::ColoredRectangle && coloredRectangle);

            std::list<std::unique_ptr<Entities::TerrainBlock>> m_terrainBlocks;
        };
    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_LEVEL_H
