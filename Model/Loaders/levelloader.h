//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_LEVELLOADER_H
#define TEUN_GAME_LEVELLOADER_H

#include <string>

class Game;

namespace Model {
    class Loaders {

    public:
        static void loadLevel(const std::string & pathToLevelXml, Game & game);
    };

} // namespace Model

#endif // TEUN_GAME_LEVELLOADER_H
