//
// Created by pc on 4/26/20.
//

#include "debrisexplosion.h"

#include "../../View/drawinterface.h"

Model::Entities::DebrisExplosion::DebrisExplosion(const Geometry::Point & position, size_t count)
{
    for (size_t i = 0; i != count; ++i) {
        m_debrisVector.emplace_back(Debris::create(position));
    }
}

void Model::Entities::DebrisExplosion::update(float dt, const Level & level, const Physics::Constants & constants)
{
    for (auto & debris : m_debrisVector) {
        debris.update(dt, level, constants);
    }
    for (auto it = m_debrisVector.begin(); it != m_debrisVector.end();) {
        if (it->shouldClean()) {
            it = m_debrisVector.erase(it);
        } else {
            ++it;
        }
    }
}

const std::list<Model::Entities::Debris> & Model::Entities::DebrisExplosion::getDebrisVector() const
{
    return m_debrisVector;
}

bool Model::Entities::DebrisExplosion::shouldClean() const
{
    //    return false;
    return m_debrisVector.empty();
}

void Model::Entities::DebrisExplosion::draw(View::Window & window) const
{
    View::DrawInterface::draw(*this, window);
}
