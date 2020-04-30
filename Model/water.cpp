//
// Created by pc on 4/30/20.
//

#include <cassert>
#include <cmath>
#include "water.h"
#include "Physics/constants.h"

Water::Water(Model::Shape::Rectangle &&rectangle) : m_rectangle(rectangle) {
    m_waves.emplace_back(3.0f, 2.0f, 50.0f);
    m_waves.emplace_back(2.0f, -1.4f, 27.0f);
    m_waves.emplace_back(2.0f, -6.4f, 17.0f);

    buildVertexArray();
}

void Water::update(float dt,
                   const Model::Entities::Level &level,
                   const Model::Physics::Constants &constants) {
    m_time += dt;
    float step = m_rectangle.width / (m_quadrilateralCount + 1.0f);
    for (size_t index = 0; index < m_quadrilateralCount + 1; ++index) {
        const float x = index * step;

        m_vertexArray[index * 2 + 1].position = {m_rectangle.left + x, m_rectangle.top +
                                                                       evalWaterHeightAt(x)};
    }
}

const Model::Shape::Rectangle &Water::getRectangle() const {
    return m_rectangle;
}

float Water::evalWaterHeightAt(float x) const {
    float y = 0.0f;
    for (const auto &wave : m_waves) {
        y += wave.m_amplitude * std::sin(x / wave.m_waveLength - wave.m_angularFrequency * m_time);
    }
    return y;
}

void Water::buildVertexArray() {
    m_vertexArray.clear();
    // ToDo TriangleStrip maken
    m_vertexArray.setPrimitiveType(sf::TriangleStrip);
    m_vertexArray.resize(2 * (m_quadrilateralCount + 1));

    float step = m_rectangle.width / (m_quadrilateralCount + 1.0f);

    for (size_t index = 0; index < m_quadrilateralCount + 1; ++index) {
        const float x = index * step;

        m_vertexArray[index * 2].position = {m_rectangle.left + x, m_rectangle.top + m_rectangle.height};
        m_vertexArray[index * 2 + 1].position = {m_rectangle.left + x, m_rectangle.top +
                                                                       evalWaterHeightAt(x)};

        m_vertexArray[index * 2].color = {0, 0, 200, 200};
        m_vertexArray[index * 2 + 1].color = {100, 90, 200, 70};
    }


}

const sf::VertexArray &Water::getVertexArray() const {
    return m_vertexArray;
}


Water::Wave::Wave(float
                  amplitude, float
                  angularFrequency, float
                  waveLength) : m_amplitude(amplitude),
                                m_angularFrequency(angularFrequency),
                                m_waveLength(waveLength) {}
