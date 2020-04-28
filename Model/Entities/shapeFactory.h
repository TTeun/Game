//
// Created by pc on 4/26/20.
//

#ifndef SFML_SHAPEFACTORY_H
#define SFML_SHAPEFACTORY_H

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Uniform;

namespace Entities {

    class ShapeFactory {

    public:
        static sf::ConvexShape buildBlob(const Uniform & numberOfPointsUniform, const Uniform & sizeUniform);
    };
} // namespace Entities

#endif // SFML_SHAPEFACTORY_H
