//
// Created by pc on 4/30/20.
//

#include "water.h"

#include "../../View/drawinterface.h"
#include "../Physics/constants.h"

#include <cassert>
#include <cmath>

Model::Entities::Water::Water(Model::Geometry::Rectangle && rectangle) : m_shape(rectangle)
{
    m_waves.emplace_back(6.0f, 1.0f, 50.0f);
    m_waves.emplace_back(3.0f, -1.4f, 27.0f);
    m_waves.emplace_back(1.0f, -9.4f, 13.5f);

    buildVertexArray();
}

void Model::Entities::Water::update(float dt,
                                    const Model::Entities::Level & level,
                                    const Model::Physics::Constants & constants)
{
    m_time += dt;
    float step = m_shape.width / (m_quadrilateralCount + 1.0f);

    for (size_t index = 0; index < m_quadrilateralCount + 1; ++index) {
        const float xLower = index * step;

        m_vertexArray[index * 2 + 1].position = {m_shape.left + xLower,
                                                 m_shape.top + 0.5f * (m_shape.height + evalWaterHeightAt(xLower))};

        const float xUpper                                                 = m_shape.width - index * step - step;
        m_vertexArray[2 * (m_quadrilateralCount + 1) + index * 2].position = {
            m_shape.left + xUpper, m_shape.top + 0.5f * (m_shape.height + evalWaterHeightAt(xUpper))};
        m_vertexArray[2 * (m_quadrilateralCount + 1) + index * 2 + 1].position = {
            m_shape.left + xUpper, m_shape.top + evalWaterHeightAt(xUpper)};
    }

    m_vertexArray[4 * (m_quadrilateralCount + 1) - 1].position = {m_shape.left, m_shape.top + evalWaterHeightAt(0)};
}

const Model::Geometry::Rectangle & Model::Entities::Water::getRectangle() const
{
    return m_shape;
}

float Model::Entities::Water::evalWaterHeightAt(float x) const
{
    float waterHeight = 0.0f;
    for (const auto & wave : m_waves) {
        waterHeight += wave.m_amplitude * std::sin(x / wave.m_waveLength - wave.m_angularFrequency * m_time);
    }
    return waterHeight;
}

void Model::Entities::Water::buildVertexArray()
{
    m_vertexArray.clear();
    m_vertexArray.setPrimitiveType(sf::TriangleStrip);
    m_vertexArray.resize(4 * (m_quadrilateralCount + 1));

    float step = m_shape.width / (m_quadrilateralCount + 1.0f);

    for (size_t index = 0; index < m_quadrilateralCount + 1; ++index) {
        const float xLower = index * step;

        m_vertexArray[index * 2].position     = {m_shape.left + xLower, m_shape.top + m_shape.height};
        m_vertexArray[index * 2 + 1].position = {m_shape.left + xLower,
                                                 m_shape.top + 0.5f * (m_shape.height + evalWaterHeightAt(xLower))};

        m_vertexArray[index * 2].color     = {25, 25, 180, 200};
        m_vertexArray[index * 2 + 1].color = {25, 85, 140, 150};
        const float xUpper                 = m_shape.width - index * step - step;

        m_vertexArray[2 * (m_quadrilateralCount + 1) + index * 2].position = {
            m_shape.left + xUpper, m_shape.top + 0.5f * (m_shape.height + evalWaterHeightAt(xUpper))};
        m_vertexArray[2 * (m_quadrilateralCount + 1) + index * 2 + 1].position = {
            m_shape.left + xUpper, m_shape.top + evalWaterHeightAt(xUpper)};

        m_vertexArray[2 * (m_quadrilateralCount + 1) + index * 2].color     = {25, 85, 140, 150};
        m_vertexArray[2 * (m_quadrilateralCount + 1) + index * 2 + 1].color = {25, 125, 150, 120};
    }

    m_vertexArray[4 * (m_quadrilateralCount + 1) - 1].position = {m_shape.left, m_shape.top + evalWaterHeightAt(0)};
}

const sf::VertexArray & Model::Entities::Water::getVertexArray() const
{
    return m_vertexArray;
}

void Model::Entities::Water::draw(View::Window & window) const
{
    View::DrawInterface::draw(*this, window);
}

Model::Entities::Water::Wave::Wave(float amplitude, float angularFrequency, float waveLength)
    : m_amplitude(amplitude), m_angularFrequency(angularFrequency), m_waveLength(waveLength)
{
}
