cmake_minimum_required(VERSION 3.16)
project(sfml)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(sfml main.cpp
        Model/Entities/player.cpp
        Model/Entities/player.h
        colors.h View/window.cpp
        View/window.h
        Model/entitycontroller.cpp Model/entitycontroller.h
        Model/Entities/debris.cpp
        Model/Entities/debris.h
        Model/Entities/debrisexplosion.cpp
        Model/Entities/debrisexplosion.h
        Model/Physics/physicsobject.h
        Model/Physics/constants.h
        Aux/uniform.h
        Model/Entities/terrainblock.cpp
        Model/Entities/terrainblock.h
        Model/Entities/level.cpp
        Model/Entities/level.h
        View/drawinterface.cpp
        View/drawinterface.h
        Model/Physics/object.h
        Model/Physics/intersectableobject.h
        Controller/keyboardhandler.cpp
        Controller/keyboardhandler.h
        game.cpp
        game.h
        Aux/uniform.cpp
        Controller/keystate.cpp
        Controller/keystate.h
        ThirdParty/inih-master/ini.c
        ThirdParty/inih-master/ini.h
        ThirdParty/inih-master/cpp/INIReader.cpp
        ThirdParty/inih-master/cpp/INIReader.h Model/Physics/constants.cpp Model/Physics/deathtimer.cpp Model/Physics/deathtimer.h Model/Physics/finiteduration.h
        ThirdParty/tinyxml/tinystr.cpp ThirdParty/tinyxml/tinystr.h ThirdParty/tinyxml/tinyxml.cpp ThirdParty/tinyxml/tinyxml.h ThirdParty/tinyxml/tinyxmlerror.cpp ThirdParty/tinyxml/tinyxmlparser.cpp
        View/tilemap.cpp View/tilemap.h Model/Loaders/levelloader.cpp Model/Loaders/levelloader.h Model/Entities/enemy.cpp Model/Entities/enemy.h Model/DataStructures/rectgraph.cpp Model/DataStructures/rectgraph.h Model/Shape/rectangle.cpp Model/Shape/rectangle.h Model/Shape/line.cpp Model/Shape/line.h Model/Shape/point.cpp Model/Shape/point.h Aux/mathtools.h Aux/mathtools.cpp Model/Physics/object.cpp Model/Physics/physicsobject.cpp Model/Physics/intersectableobject.cpp Aux/constpointerwrapper.h)

# Find SFML
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

target_link_libraries(sfml
        PUBLIC
        sfml-graphics sfml-audio sfml-window sfml-system)