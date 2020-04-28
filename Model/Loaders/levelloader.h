//
// Created by pc on 4/27/20.
//

#ifndef SFML_LEVELLOADER_H
#define SFML_LEVELLOADER_H

#include <string>

class Game;

namespace Model {
    class Loaders {

    public:
        static void loadLevel(std::string pathToLevelXml, Game & game);
    };

} // namespace Model

#endif // SFML_LEVELLOADER_H
