#include "debris.h"

Entities::Debris::Debris(const sf::Vector2f & position, const Uniform & sizeUniform, const Uniform & velocityUniform)
    : IntersectableObject(
          Rectangle({static_cast<float>(sizeUniform.get()), static_cast<float>(sizeUniform.get())}, position)),
      Physics::DeathTimer(Uniform(20, 20).get() / 10.0f)
{
    setVelocity(getRandomVelocity(velocityUniform));
}

Point Entities::Debris::getRandomVelocity(const Uniform & directionUniform)
{
    Point direction(sf::Vector2f(rand() / 2 + 1, rand() / 2 + 1));
    direction *= static_cast<float>(directionUniform.get());
    return direction;
}
