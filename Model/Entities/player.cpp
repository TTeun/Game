//
// Created by pc on 4/26/20.
//

#include "player.h"
#include "../../View/drawinterface.h"

Model::Entities::Player::Player(float x, float y, float height, float width, const sf::Color &color)
        : Physics::IntersectableObject(
        Model::Shapes::ColoredRectangle(Model::Shapes::Point{width, height}, Model::Shapes::Point{x, y}, color)) {
    setFeelsGravity(true);
//    m_shape.setColor(color);
}

void Model::Entities::Player::addHorizontalForce(float force) {
    m_velocity.x += force / m_mass;
}

void Model::Entities::Player::jump(const Physics::Constants &constants) {
    if (m_snappedTerrainBlock) {
        switch (m_whereIsSnappedTerrain) {
            case Physics::IntersectableObject::WHERE_IS_SNAPPED_TERRAIN::BELOW:
                m_velocity.y = -constants.m_jumpVelocity;
                m_snappedTerrainBlock.set(nullptr);
                break;
            case Physics::IntersectableObject::WHERE_IS_SNAPPED_TERRAIN::RIGHT:
                m_velocity.y = -constants.m_wallJumpYVelocity;
                m_velocity.x = -constants.m_wallJumpXVelocity;
                m_snappedTerrainBlock.set(nullptr);
                break;
            case Physics::IntersectableObject::WHERE_IS_SNAPPED_TERRAIN::LEFT:
                m_velocity.y = -constants.m_wallJumpYVelocity;
                m_velocity.x = constants.m_wallJumpXVelocity;
                m_snappedTerrainBlock.set(nullptr);
                break;
            case Physics::IntersectableObject::WHERE_IS_SNAPPED_TERRAIN::ABOVE:
                break;
        }
    }
}

void Model::Entities::Player::checkAndHandlePressedIntoWall(float dt, const Model::Physics::Constants &constants) {
    if (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::RIGHT) {
        const auto movedRect = m_shape + m_shape.width * 0.5f * Model::Shapes::Point{1.0f, 0.0f};
        if (not m_snappedTerrainBlock.get().getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(nullptr);
        }
        bool isPressingIntoWall = m_velocity.x > 0.0f;
        applyGravity(dt, constants);
        if (isPressingIntoWall) {
            m_velocity.x = 0.0f;
            if (m_velocity.y > 40.0f) {
                m_velocity.y = 40.0f;
            }
        } else {
            m_snappedTerrainBlock.set(nullptr);
        }
    } else if (m_whereIsSnappedTerrain == WHERE_IS_SNAPPED_TERRAIN::LEFT) {
        const auto movedRect = m_shape + m_shape.width * 0.5f * Model::Shapes::Point{-1.0f, 0.0f};
        if (not m_snappedTerrainBlock.get().getShape().intersects(movedRect)) {
            m_snappedTerrainBlock.set(nullptr);
        }
        bool isPressingIntoWall = m_velocity.x < 0.0f;
        applyGravity(dt, constants);
        if (isPressingIntoWall) {
            m_velocity.x = 0.0f;
            if (m_velocity.y > 40.0f) {
                m_velocity.y = 40.0f;
            }
        } else {
            m_snappedTerrainBlock.set(nullptr);
        }
    }
}

void Model::Entities::Player::draw(View::Window &window) const {
    View::DrawInterface::draw(*this, window);
}
