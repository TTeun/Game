//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_DRAWINTERFACE_H
#define TEUN_GAME_DRAWINTERFACE_H

namespace Model {
    class EntityController;

    class Loaders;
} // namespace Model

namespace Model {
    class EntityController;

    namespace DataStructures {
        class RectGraph;
    }

    namespace Entities {
        class Level;

        class DebrisExplosion;

        class Enemy;

        class Debris;

        class EntityController;

        class Player;

        class Water;

    } // namespace Entities

} // namespace Model

namespace View {

    class Window;

    class DrawInterface {

        friend class Model::Loaders;

    public:
        void drawModel(Window & window, const Model::Entities::EntityController & entityController);

        static void draw(const Model::Entities::Enemy & enemy, View::Window & window);

        static void draw(const Model::Entities::Level & enemy, View::Window & window);

        static void draw(const Model::Entities::Debris & enemy, View::Window & window);

        static void draw(const Model::Entities::DebrisExplosion & debrisExplosion, View::Window & window);

        static void draw(const Model::Entities::EntityController & entityController, View::Window & window);

        static void draw(const Model::Entities::Player & player, View::Window & window);

        static void draw(const Model::DataStructures::RectGraph & rectGraph, View::Window & window);

        static void draw(const Model::Entities::Water & player, View::Window & window);
    };
} // namespace View

#endif // TEUN_GAME_DRAWINTERFACE_H
