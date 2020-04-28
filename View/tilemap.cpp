//
// Created by pc on 4/27/20.
//

#include "tilemap.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

TileMap::TileMap(const std::string & tileSet, sf::Vector2u tileSize, size_t width, size_t height)
{
    m_wasLoadedCorrectly = load(tileSet, tileSize, width, height);
}

bool TileMap::load(const std::string & tileSet, sf::Vector2u tileSize, size_t widthInPoints, size_t heightInPoints)
{
    if (!m_tileSet.loadFromFile(tileSet)) {
        return false;
    }
    const size_t width  = widthInPoints / tileSize.x;
    const size_t height = heightInPoints / tileSize.y;

    const size_t heightRemainder = heightInPoints % tileSize.y;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * (height + (heightRemainder > 0 ? 1 : 0)) * 4);
    bool heightIsFractional = heightRemainder != 0;

    size_t count = 0;
    size_t tileNumber;
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            ++count;

            if (i == 0) {
                if (j == 0) {
                    tileNumber = 0;
                } else if ((j == height - 1) && (not heightIsFractional)) {
                    tileNumber = 15;
                } else {
                    tileNumber = 5;
                }
            } else if (i == width - 1) {
                if (j == 0) {
                    tileNumber = 3;
                } else if ((j == height - 1) && (not heightIsFractional)) {
                    tileNumber = 18;
                } else {
                    tileNumber = 8;
                }
            } else {
                if (j == 0) {
                    tileNumber = 1 + i % 2;
                } else if ((j == height - 1) && (not heightIsFractional)) {
                    tileNumber = 16 + i % 2;
                } else {
                    tileNumber = 6 + i % 2;
                }
            }

            size_t tu = tileNumber % (m_tileSet.getSize().x / tileSize.x);
            size_t tv = tileNumber / (m_tileSet.getSize().x / tileSize.x);

            sf::Vertex * quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    bool heightIsLessThanOne = height == 0;

    if (heightRemainder > 0) {
        for (size_t i = 0; i < width; ++i) {
            sf::Vertex * quad = &m_vertices[count * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, height * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, height * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, height * tileSize.y + heightRemainder);
            quad[3].position = sf::Vector2f(i * tileSize.x, height * tileSize.y + heightRemainder);

            if (i == 0) {
                if (heightIsLessThanOne) {
                    tileNumber = 0;
                } else {
                    tileNumber = 15;
                }
            } else if (i == width - 1) {
                if (heightIsLessThanOne) {
                    tileNumber = 3;
                } else {
                    tileNumber = 18;
                }
            } else {
                if (heightIsLessThanOne) {
                    tileNumber = 1 + i % 2;
                } else {
                    tileNumber = 16 + i % 2;
                }
            }

            size_t tu = tileNumber % (m_tileSet.getSize().x / tileSize.x);
            size_t tv = tileNumber / (m_tileSet.getSize().x / tileSize.x);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y + heightRemainder);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y + heightRemainder);

            ++count;
        }
    }

    return true;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates renderStates) const
{
    renderStates.transform *= getTransform();
    renderStates.texture = &m_tileSet;
    target.draw(m_vertices, renderStates);
}

bool TileMap::wasLoadedCorrectly() const
{
    return m_wasLoadedCorrectly;
}
