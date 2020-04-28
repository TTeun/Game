#include "debris.h"

#include "../../Aux/uniform.h"
#include "shapeFactory.h"

Entities::Debris::Debris(const sf::Vector2f & position,
                         const sf::Color & color,
                         const sf::Color & outlineColor,
                         const Uniform & sizeUniform,
                         const Uniform & directionUniform,
                         const Uniform & numberOfPointsUniform)
    : IntersectableObject(ShapeFactory::buildBlob(numberOfPointsUniform, sizeUniform),
                          getNormalizedRandomDirection(directionUniform)),
      Physics::DeathTimer(Uniform(20, 20).get() / 10.0f)
{
    setVelocity(getNormalizedRandomDirection(directionUniform));

    m_shape.setOutlineThickness(1.0f);
    m_shape.setPosition(position);

    m_shape.setFillColor(color);
    m_shape.setOutlineColor(outlineColor);
}

sf::Vector2f Entities::Debris::getNormalizedRandomDirection(const Uniform & directionUniform)
{
    sf::Vector2f direction(sf::Vector2f(rand() / 2 + 1, rand() / 2 + 1));
    direction /= static_cast<float>(sqrt(direction.x * direction.x + direction.y * direction.y));
    direction.x = (rand() % 2 == 1 ? 1.0f : (-1.0f)) * direction.x;
    direction.y = (rand() % 2 == 1 ? 1.0f : (-1.0f)) * direction.y;
    direction *= static_cast<float>(directionUniform.get());
    return direction;
}
