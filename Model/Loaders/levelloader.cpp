#include "levelloader.h"

#include "../../ThirdParty/tinyxml/tinyxml.h"
#include "../../game.h"

#include <iostream>

static float stringToFloat(const char * str)
{
    return static_cast<float>(atof(str));
}

static Model::Geometry::ColoredRectangle getRect(const TiXmlElement * blockElement)
{
    const float x      = stringToFloat(blockElement->Attribute("x"));
    const float y      = stringToFloat(blockElement->Attribute("y"));
    const float width  = stringToFloat(blockElement->Attribute("width"));
    const float height = stringToFloat(blockElement->Attribute("height"));

    return {{width, height}, {x, y}, {0, 255, 0}};
}

void Model::Loaders::loadLevel(const std::string & pathToLevelXml, Game & game)
{
    auto * level = new Entities::Level();
    //    View::DrawInterface &drawInterface = game.getDrawInterface();
    //    drawInterface.m_levelTileMaps.clear();

    TiXmlDocument doc(pathToLevelXml.c_str());
    bool loadOkay = doc.LoadFile();
    if (!loadOkay) {
        std::cout << "Could not load test file '../Config/Levels/level1.xml'. Error=" << doc.ErrorDesc() << '\n';
    }

    const TiXmlElement * levelElement = doc.FirstChildElement();
    std::cout << "Loading level " << doc.FirstChildElement()->Attribute("name") << '\n';

    const TiXmlElement * blockElement = levelElement->FirstChildElement();

    while (blockElement) {
        const size_t id = level->addTerrainBlock(getRect(blockElement));
        //        auto *tileMap = new View::TileMap("../Assets/images/Tileset_ground.png",
        //                                          {32, 32},
        //                                          static_cast<size_t>(rectangle.m_width),
        //                                          static_cast<size_t>(rectangle.m_height));
        //        if (tileMap->wasLoadedCorrectly()) {
        //            tileMap->setPosition({rectangle.m_x, rectangle.m_y});
        //            drawInterface.addLevelTileMap(id, tileMap);
        //        } else {
        //            drawInterface.addLevelTileMap(id, nullptr);
        //        }
        blockElement = blockElement->NextSiblingElement();
    }

    game.getEntityController().setLevel(std::unique_ptr<Entities::Level>(level));
}
