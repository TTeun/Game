#include "debris.h"

#include "../../View/drawinterface.h"

Model::Entities::Debris::Debris(const sf::Vector2f &position,
                                const Aux::Uniform &sizeUniform,
                                const Aux::Uniform &velocityUniform)
        : IntersectableObject(Model::Shapes::ColoredRectangle(
        {static_cast<float>(sizeUniform.get()), static_cast<float>(sizeUniform.get())}, position, sf::Color::Red)),
          Physics::DeathTimer(Aux::Uniform(20, 20).get() / 10.0f) {
    setVelocity(getRandomVelocity(velocityUniform));
}

Model::Shapes::Point Model::Entities::Debris::getRandomVelocity(const Aux::Uniform &velocityUniform) {
    Model::Shapes::Point direction(
            sf::Vector2f(static_cast<float>(Aux::Uniform(0, 15).get()), static_cast<float>(Aux::Uniform(0, 15).get())));
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

Model::Entities::Debris Model::Entities::Debris::create(const sf::Vector2f &position) {
    return Debris{position, {10, 5}, {53, 5}};
}

void Model::Entities::Debris::draw(View::Window &window) const {
    View::DrawInterface::draw(*this, window);
}
