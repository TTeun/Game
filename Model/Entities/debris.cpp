#include "debris.h"

Model::Entities::Debris::Debris(const sf::Vector2f & position,
                                const Uniform & sizeUniform,
                                const Uniform & velocityUniform)
    : PhysicsObject(Model::Shape::Rectangle(
          {static_cast<float>(sizeUniform.get()), static_cast<float>(sizeUniform.get())}, position)),
      Physics::DeathTimer(Uniform(20, 20).get() / 10.0f)
{
    setVelocity(getRandomVelocity(velocityUniform));
    m_shape.setColor(sf::Color::Black);
}

Model::Shape::Point Model::Entities::Debris::getRandomVelocity(const Uniform & velocityUniform)
{
    Model::Shape::Point direction(
        sf::Vector2f(static_cast<float>(Uniform(0, 15).get()), static_cast<float>(Uniform(0, 15).get())));
    direction.normalize();
    if (rand() % 2 == 0) {
        direction.x *= -1;
    }
    if (rand() % 2 == 0) {
        direction.y *= -1;
    }
    direction *= static_cast<float>(velocityUniform.get());
    return direction;
}

Model::Entities::Debris Model::Entities::Debris::create(const sf::Vector2f & position)
{
    return Debris{position, {10, 5}, {53, 5}};
}
