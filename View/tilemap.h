//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_TILEMAP_H
#define TEUN_GAME_TILEMAP_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <string>

namespace sf {
    class Drawable;

    class RenderTarget;
} // namespace sf

namespace View {

    class TileMap : public sf::Drawable, public sf::Transformable {
    public:
        TileMap(const std::string &tileSet, sf::Vector2u tileSize, size_t width, size_t height);

        bool wasLoadedCorrectly() const;

        bool load(const std::string &tileSet, sf::Vector2u tileSize, size_t width, size_t height);

        virtual void draw(sf::RenderTarget &target, sf::RenderStates renderStates) const;

    private:
        bool m_wasLoadedCorrectly;
        sf::VertexArray m_vertices;
        sf::Texture m_tileSet;
    };
} // namespace View

#endif // TEUN_GAME_TILEMAP_H
