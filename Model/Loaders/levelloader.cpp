#include "levelloader.h"

#include "../../ThirdParty/tinyxml/tinyxml.h"
#include "../../game.h"

#include <iostream>

struct rect {
    float x, y, width, height;
};

static float stringToFloat(const char * str)
{
    return static_cast<float>(atof(str));
}

static rect getRect(const TiXmlElement * blockElement)
{
    const float x      = stringToFloat(blockElement->Attribute("x"));
    const float y      = stringToFloat(blockElement->Attribute("y"));
    const float width  = stringToFloat(blockElement->Attribute("width"));
    const float height = stringToFloat(blockElement->Attribute("height"));

    return {x, y, width, height};
}

void Model::Loaders::loadLevel(std::string pathToLevelXml, Game & game)
{
    Entities::Level * level             = new Entities::Level();
    View::DrawInterface & drawInterface = game.getDrawInterface();
    drawInterface.m_levelTileMaps.clear();

    TiXmlDocument doc(pathToLevelXml.c_str());
    bool loadOkay = doc.LoadFile();
    if (!loadOkay) {
        std::cout << "Could not load test file '../Config/Levels/level1.xml'. Error=" << doc.ErrorDesc() << '\n';
    }

    const TiXmlElement * levelElement = doc.FirstChildElement();
    std::cout << "Loading level " << doc.FirstChildElement()->Attribute("name") << '\n';

    const TiXmlElement * blockElement = levelElement->FirstChildElement();

    while (blockElement) {
        const auto rectangle = getRect(blockElement);
        const size_t id      = level->addTerrainBlock(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
        auto * tileMap       = new TileMap("../Assets/images/Tileset_ground.png",
                                     {32, 32},
                                     static_cast<size_t>(rectangle.width),
                                     static_cast<size_t>(rectangle.height));
        if (tileMap->wasLoadedCorrectly()) {
            tileMap->setPosition({rectangle.x, rectangle.y});
            drawInterface.addLevelTileMap(id, tileMap);
        } else {
            drawInterface.addLevelTileMap(id, nullptr);
        }
        blockElement = blockElement->NextSiblingElement();
    }

    game.getModel().setLevel(level);
}
