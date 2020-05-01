//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_WATER_H
#define TEUN_GAME_WATER_H

#include "Entities/level.h"
#include "Shapes/quadrilateral.h"
#include "../View/drawable.h"

namespace Model {
    namespace Physics {
        class Constants;
    }
}

class Water : public View::Drawable {

public:
    Water(Model::Shapes::Rectangle &&rectangle);

    void draw(View::Window &window) const override;

    void update(float dt,
                const Model::Entities::Level &level,
                const Model::Physics::Constants &constants);


    const Model::Shapes::Rectangle &getRectangle() const;

    const sf::VertexArray &getVertexArray() const;

private:

    void buildVertexArray();

    sf::VertexArray m_vertexArray;

    float evalWaterHeightAt(float x) const;

    class Wave {
    public:
        Wave(float amplitude, float angularFrequency, float waveLength);

        const float m_amplitude;
        const float m_waveLength;
        const float m_angularFrequency;
    };


    std::vector<Wave> m_waves;

    const Model::Shapes::Rectangle m_shape;

    float m_time = 0.0f;

    const size_t m_quadrilateralCount = 25;

};


#endif //TEUN_GAME_WATER_H
