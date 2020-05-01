//
// Created by pc on 5/1/20.
//

#ifndef TEUN_GAME_DRAWABLE_H
#define TEUN_GAME_DRAWABLE_H

namespace Model {
    namespace Geometry {
        class Rectangle;
    }
} // namespace Model

namespace View {

    class DrawInterface;

    class Window;

    class Drawable {

    public:
        virtual void draw(View::Window & window) const = 0;
    };
} // namespace View

#endif // TEUN_GAME_DRAWABLE_H
