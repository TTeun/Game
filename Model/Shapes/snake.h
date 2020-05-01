//
// Created by pc on 5/1/20.
//

#ifndef TEUN_GAME_SNAKE_H
#define TEUN_GAME_SNAKE_H

#include <vector>
#include <memory>
#include "coloredrectangle.h"

namespace Model {
    namespace Shapes {


        class Snake : public ColoredRectangle {

        public:
            Snake(const sf::FloatRect &rectangle, const sf::Color &color);

        private:
            std::vector<std::unique_ptr<Model::Shapes::ColoredRectangle>> m_followRectangles;

        };

    }

}

#endif //TEUN_GAME_SNAKE_H
