//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_WATER_H
#define TEUN_GAME_WATER_H

#include "Entities/level.h"
#include "Shape/quadrilateral.h"

namespace Model {
    namespace Physics {
        class Constants;
    }
}

class Water {

public:
    Water(Model::Shape::Rectangle &&rectangle);


    void update(float dt,
                const Model::Entities::Level &level,
                const Model::Physics::Constants &constants);


    const Model::Shape::Rectangle &getRectangle() const;

    const sf::VertexArray &getVertexArray() const;

private:

    void buildVertexArray();

    sf::VertexArray m_vertexArray;

    float evalWaterHeightAt(float x) const;

    class Wave {
    public:
        Wave(float amplitude, float angularFrequency, float waveLength);

        float m_amplitude = 1.0f;
        float m_waveLength = 50.0f;
        float m_angularFrequency = 2.0f;
    };


    std::vector<Wave> m_waves;

    const Model::Shape::Rectangle m_rectangle;

    float m_time = 0.0f;

    const size_t m_quadrilateralCount = 20;

};


#endif //TEUN_GAME_WATER_H
